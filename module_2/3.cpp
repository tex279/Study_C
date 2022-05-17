#include <iostream>
#include <vector>
#include <cassert>
#include <queue>


//    Постройте B-дерево минимального порядка t и выведите его по слоям.
//    В качестве ключа используются числа, лежащие в диапазоне 0..2^32 -1

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

    bool IsNodeFull(Node<T> *node);

    void SplitChild(Node<T> *node, size_t index);

    void AddNonFull(Node<T> *node, const T &data);

    void DebugPrint(Node<T> *node, size_t indent);

public:
    BTree(const size_t min_degree) : t(min_degree), root(nullptr), size(0) { assert(min_degree >= 2); }

    ~BTree();

    void Add(const T &data);

    void DebugPrint();

    void Print();

    size_t Size() const;
};

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::Print() {
    std::queue < Node<T> * > s;

    s.push(root);

    while (!s.empty()) {
        Node<T> *tmp = s.front();
        s.pop();

        std::cout << *tmp;

        for (size_t i = 0; i < tmp->children.size(); ++i) {
            s.push(tmp->children[i]);
        }
    }
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::SplitChild(Node<T> *node, size_t index) {
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
        size_t count_child = node->children[index]->children.size() - 1;

        for (size_t i = 0; i < t; ++i) {
            new_child->children.push_back(node->children[index]->children[i + t]);
        }


        for (size_t i = 0; i < t; ++i) {
            node->children[index]->children.pop_back();
        }
    }

    node->children[index]->keys.pop_back();

    node->children.push_back(new_child);
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::DebugPrint() {
    DebugPrint(root, 0);
}

template<typename T, typename CompareRule>
void BTree<T, CompareRule>::DebugPrint(Node<T> *node, size_t indent) {
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
bool BTree<T, CompareRule>::IsNodeFull(Node<T> *node) {
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

        while (pos >= 0 && data < node->keys[pos]) {
            node->keys[pos + 1] = node->keys[pos];

            --pos;
        }

        node->keys[pos + 1] = data;
    } else {
        while (pos >= 0 && data < node->keys[pos]) {
            --pos;
        }

        if (IsNodeFull(node->children[pos + 1])) {
            SplitChild(node, pos + 1);

            if (data > node->keys[pos + 1]) {
                ++pos;
            }
        }

        AddNonFull(node->children[pos + 1], data);
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

    b_tree.DebugPrint();

    b_tree.Print();
}

int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}