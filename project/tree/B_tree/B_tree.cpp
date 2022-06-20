#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

//    Постройте shortest_path_root_list-дерево минимального порядка t и выведите его по слоям.
//    В качестве ключа используются числа, лежащие в диапазоне 0..binary_tree.txt.txt.txt^32 -structs

template<typename T>
struct Node {
    bool leaf;

    std::vector <T> keys;
    std::vector<Node *> children;

    Node(bool leaf) : leaf(leaf) {}

    ~Node();

    friend std::ostream& operator<<(std::ostream &os, const Node<T> &it)  {
        for (auto &data: it.keys) {
            os << data << " ";
        }

        return os;
    }

    Node &operator = (const Node &other) = default;
};

template<typename T>
Node<T>::~Node() {
    for (auto child: children) {
        delete child;
    }
}

template<typename T>
class Less {
public:
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<typename T, typename CompareRule = Less<T>>
class BTree {
    CompareRule rule;

    size_t t;

    size_t size;

    Node<T> *root;

    bool IsNodeFull(const Node<T> *node) const;

    void SplitChild(Node<T> *node, const size_t index);

    void AddNonFull(Node<T> *node, const T &data);

    void DebugPrint(const Node<T> *node, size_t indent) const;

    void Print(std::queue<Node<T> *> &level) const;

public:
    BTree(const size_t min_degree) : t(min_degree), root(nullptr), size(0) { assert(min_degree >= 2); }

    ~BTree();

    void Add(const T &data);

    void DebugPrint() const;

    void Print() const;

    size_t Size() const;

    friend void testBTree();
};

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::Print(std::queue<Node<T> *> &level) const {
    if (level.empty()) {
        return;
    }

    std::queue<Node<T>* > new_level;

    while (!level.empty()) {
        Node<T> *tmp = level.front();
        level.pop();

        std::cout << *tmp;


        for (auto &child: tmp->children) {
            new_level.push(child);
        }
    }

    std::cout << std::endl;

    Print(new_level);
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::Print() const {
    if (!size || root->keys.empty()) {
        return;
    }

    std::queue<Node<T> *> q;
    q.push(root);

    Print(q);

}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::SplitChild(Node<T> *node, const size_t index) {
    Node<T> *new_child = new Node<T>(node->children[index]->leaf);
    ++size;

    for (size_t i = 0; i < t - 1; ++i) {
        new_child->keys.push_back(node->children[index]->keys[i + t]);
    }

    for (size_t i = 0; i < t - 1; ++i) {
        node->children[index]->keys.pop_back();
    }

    ssize_t pos = node->keys.size() - 1;

    T mid = node->children[index]->keys[t - 1];

    node->keys.resize(node->keys.size() + 1);
    while (pos >= 0 && mid < node->keys[pos]) {
        node->keys[pos + 1] = node->keys[pos];

        --pos;
    }

    node->keys[pos + 1] = mid;

    if (!node->children[index]->leaf) {
        for (size_t i = 0; i < t; ++i) {
            new_child->children.push_back(node->children[index]->children[i +  t ]);
        }

        for (size_t i = 0; i < t; ++i) {
            node->children[index]->children.pop_back();
        }
    }

    node->children[index]->keys.pop_back();

    ssize_t pos_child = node->keys.size() - 1;

    node->children.resize(node->keys.size() + 1);
    while (pos_child >= 0 && mid < node->keys[pos_child]) {
        node->children[pos_child + 1] = node->children[pos_child];

        --pos_child;
    }

    node->children[pos_child + 1] = new_child;
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::DebugPrint() const {
    if (!size || root->keys.empty()) {
        return;
    }

    DebugPrint(root, 0);
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::DebugPrint(const Node<T> *node, size_t indent) const {
    std::cout << std::string(indent, ' ');
    std::cout << "data: [";

    for (auto it = node->keys.begin(); it != node->keys.end(); it++) {
        std::cout << (*it);
        if (it + 1 != node->keys.end())
            std::cout << ", ";
    }

    std::cout << "]" << std::endl;

    for (auto child: node->children) {
        DebugPrint(child, indent + 4);
    }
}

template<typename T, typename CompareRule>
BTree<T, CompareRule>::~BTree() {
    if (root) {
        delete root;
    }
}

template<typename T, typename CompareRule>
bool BTree<T, CompareRule>::IsNodeFull(const Node<T> *node) const {
    return node->keys.size() == 2 * t - 1;
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::Add(const T &data) {
    if (!root) {
        root = new Node<T>(true);
        ++size;
    }

    if (IsNodeFull(root)) {
        Node<T> *new_root = new Node<T>(false);
        ++size;

        new_root->children.push_back(root);

        root = new_root;

        SplitChild(root, 0);
    }

    AddNonFull(root, data);
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::AddNonFull(Node<T> *node, const T &data) {
    ssize_t pos = node->keys.size() - 1;

    if (node->leaf) {
        node->keys.resize(node->keys.size() + 1);

        while (pos >= 0 &&  rule(data, node->keys[pos])) {
            node->keys[pos + 1] = node->keys[pos];

            --pos;
        }

        node->keys[pos + 1] = data;
    } else {
        while (pos >= 0 &&  rule(data, node->keys[pos])) {
            --pos;
        }

        if (IsNodeFull(node->children[pos + 1])) {
            SplitChild(node, pos + 1);

            if (rule(node->keys[pos + 1], data)) {
                ++pos;
            }
        }

        AddNonFull(node->children[pos + 1], data);
    }
}


void testBTree()
{
    BTree<char> tree(3);

    tree.root = new Node<char>(false);
    tree.root->keys = {'G', 'M', 'P', 'X'};

    {
        auto child = new Node<char>(true);
        child->keys = {'A', 'C', 'D', 'E'};
        tree.root->children.push_back(child);
    }

    {
        auto child = new Node<char>(true);
        child->keys = {'J', 'K'};
        tree.root->children.push_back(child);
    }
    {
        auto child =  new Node<char>(true);
        child->keys = {'N', 'O'};
        tree.root->children.push_back(child);
    }
    {
        auto child =  new Node<char>(true);
        child->keys = {'R', 'S', 'T', 'U', 'V'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new Node<char>(true);
        child->keys = {'Y', 'Z'};
        tree.root->children.push_back(child);
    }

    std::cout << "Initial tree:" << std::endl;
    tree.DebugPrint();
    std::cout << std::endl;

    std::string insertKeys = "BQLF";
    // посимвольно добавляем в дерево ключи
    for (auto c: insertKeys)
    {
        tree.Add(c);
        std::cout << "After inserting " << c << ":" << std::endl;
        tree.DebugPrint();
        std::cout << std::endl;
    }
}


void run(std::istream &input, std::ostream &output) {
    size_t n;

    input >> n;

    BTree<size_t> b_tree(n);

    size_t tmp;

    while (input >> tmp) {
        b_tree.Add(tmp);
    }

    //  b_tree.DebugPrint();

    b_tree.Print();
}

int main() {
    run(std::cin, std::cout);

//    testBTree();

    return EXIT_SUCCESS;
}