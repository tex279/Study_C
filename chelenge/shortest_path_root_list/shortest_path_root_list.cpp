#include <iostream>
#include <stack>
#include <queue>

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

    bool CheckOneValue() const;

    size_t CheckMinHeight() const;

    void Print(std::ostream &ostream) const;

    BinaryTree() : root(nullptr), size(0) {};

    ~BinaryTree();
};

template<typename T, typename CompareRule>
BinaryTree<T, CompareRule>::~BinaryTree() {
    if (IsEmpty()) {
        return;
    }

    std::stack < Node<T> * > s;

    s.push(root);

    while (!s.empty()) {
        Node<T> *tmp = s.top();
        s.pop();

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }

        delete tmp;
    }
}

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
        parent = cur;

        if (rule(cur->data, key)) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    if (!cur) {
        return false;
    }

    Node<T> *removed = nullptr;

    if (cur->left == NULL || cur->right == NULL) {
        Node<T> *child = nullptr;
        removed = cur;

        if (cur->left) {
            child = cur->left;
        } else if (cur->right) {
            child = cur->right;
        }

        if (!parent) {
            root = child;
        } else if (parent->left == cur) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    } else {
        Node<T> *most_left = cur->right;
        Node<T> *most_left_parent = cur;

        while (most_left->left != NULL) {
            most_left_parent = most_left;
            most_left = most_left->left;
        }

        cur->data = most_left->data;
        removed = most_left;

        if (most_left_parent->left == most_left) {
            most_left_parent->left = NULL;
        } else {
            most_left_parent->right = most_left->right;
        }
    }

    delete removed;

    --size;

    return true;
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

    std::stack < Node<T> * > s;

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

template<typename T, typename CompareRule>
bool BinaryTree<T, CompareRule>::CheckOneValue() const {
    if (IsEmpty()) {
        return false;
    }

    std::stack < Node<T> * > s;

    s.push(root);

    while (!s.empty()) {
        Node<T> *tmp = s.top();
        s.pop();

        if (tmp->data != root->data) {
            return false;
        }

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }

    return true;
}

template<typename T, typename CompareRule>
size_t BinaryTree<T, CompareRule>::CheckMinHeight() const {
    if (IsEmpty()) {
        return 0;
    }

    size_t height = 1;

    std::queue< Node<T> * > s;

    s.push(root);

    while (!s.empty()) {
        Node<T> *tmp = s.front();
        s.pop();

        if (!tmp->right && !tmp->left) {
            return height;
        }

        ++height;

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }

    return true;
}

void run(std::istream &input, std::ostream &output) {
    BinaryTree<int> tree;

    int buf = 0;
    while (input >> buf) {
        tree.Add(buf);
    }

    output << tree.CheckMinHeight() << std::endl;
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
