#include <iostream>
#include <stack>

template<typename T>
struct Node {
    T data;

    Node *left;
    Node *right;

    Node() = default;

    Node(const T &data) : data(data), left(nullptr), right(nullptr) {};

    ~Node() = default;
};

template<typename T>
class Less {
public:
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<typename T, typename CompareRule = Less<T>>
class BinaryTree {
    Node<T> *root;

    CompareRule rule;

    size_t size;
public:
    bool IsEmpty() const;

    bool Add(const T &key);

    bool Delete(const T &key);

    bool Search(const T &key) const;

    void Print(std::ostream &ostream) const;

    BinaryTree() : root(nullptr), size(0) {};

    ~BinaryTree() = default;
};

template<typename T, typename CompareRule>
bool BinaryTree<T, CompareRule>::IsEmpty() const {
    return !size;
}

template<typename T, typename CompareRule>
bool BinaryTree<T, CompareRule>::Add(const T &key) {
    Node<T> **cur = &root;

    while (*cur) {
        Node<T> &node = **cur;

        if (rule(node.data, key)) {
            cur = &node.right;
        } else {
            cur = &node.left;
        }
    }

    *cur = new Node<T>(key);

    ++size;

    return true;
}

template<typename T, typename CompareRule>
bool BinaryTree<T, CompareRule>::Delete(const T &key) {
    Node<T> *cur = root;

    Node<T> *parent = nullptr;

    while (cur && cur->data != key) {
        Node<T> *node = cur;

        if (node->data == key) {

            return true;
        }  if (rule(node->data, key)) {
            parent = cur;
            cur = node->right;
        } else {
            parent = cur;
            cur = node->left;
        }
    }

    return false;
}

template<typename T, typename CompareRule>
bool BinaryTree<T, CompareRule>::Search(const T &key) const {
    Node<T> *tmp = root;

    while (tmp) {
        if (tmp->data == key) {
            return true;
        } else if (rule(tmp->data, key)) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }

    return false;
}

template<typename T, typename CompareRule>
void BinaryTree<T, CompareRule>::Print(std::ostream &ostream) const {
    if (IsEmpty()) {
        return;
    }

    std::stack <Node<T>*> s;

    s.push(root);

    while (!s.empty()) {
        Node<T> *tmp = s.top();
        s.pop();
        ostream << tmp->data << " ";

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

void run(std::istream &input, std::ostream &output) {
    BinaryTree<long int> tree;

    size_t n = 0;

    input >> n;

    size_t buf = 0;
    for (size_t i = 0; i < n; ++i) {
        input >> buf;

        tree.Add(buf);
    }

    tree.Print(output);

    output << std::endl;

    tree.Delete(3);

    tree.Print(output);
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
