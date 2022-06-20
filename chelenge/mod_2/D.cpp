#include <iostream>

template<typename T>
struct Node {
    T data;

    size_t height;

    Node *left;
    Node *right;

    Node(const T &data) : data(data), height(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class Less {
public:
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<typename T, typename CompareRule = Less<T>>
class AvlTree {
    CompareRule rule;

    Node<T> *root;

    void DestroyTree(Node<T> *node);

    Node<T> *DeleteInternal(Node<T> *node, const T &data);

    Node<T> *FindMin(Node<T> *node);

    Node<T> *RemoveMin(Node<T> *node);

    Node<T> *AddInternal(Node<T> *node, const T &data);

    size_t GetHeight(Node<T> *node);

    void FixHeight(Node<T> *node);

    Node<T> *RotateLeft(Node<T> *node);

    Node<T> *RotateRight(Node<T> *node);

    int GetBalance(Node<T> *node);

    Node<T> *DoBalance(Node<T> *node);

public:
    AvlTree() : root(nullptr) {}

    ~AvlTree();

    void Add(const T &data);

    bool Search(const T &data);

    T SearchNext(const T &data);

    T SearchPrev(const T &data);

    void Delete(const T &data);
};

template<typename T, typename CompareRule>
        void AvlTree<T, CompareRule>::DestroyTree(Node<T> *node) {
    if (node) {
        DestroyTree(node->left);
        DestroyTree(node->right);

        delete node;
    }
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::DeleteInternal(Node<T> *node, const T &data) {
    if (!node) {
        return nullptr;
    }

    if (rule(node->data, data)) {
        node->right = DeleteInternal(node->right, data);
    } else if (rule(data, node->data)) {
        node->left = DeleteInternal(node->left, data);
    } else {
        Node<T> *left = node->left;
        Node<T> *right = node->right;

        delete node;

        if (!right) {
            return left;
        }

        Node<T> *min = FindMin(right);
        min->right = RemoveMin(right);
        min->left = left;

        return DoBalance(min);
    }

    return DoBalance(node);
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::FindMin(Node<T> *node) {
    while (node->left) {
        node = node->left;
    }

    return node;
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::RemoveMin(Node<T> *node) {
    if (!node->left) {
        return node->right;
    }

    node->left = RemoveMin(node->left);

    return DoBalance(node);
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::AddInternal(Node<T> *node, const T &data) {
    if (!node) {
        return new Node(data);
    }

    if (rule(data, node->data)) {
        node->left = AddInternal(node->left, data);
    } else if (data == node->data) {
        return nullptr;
    } else {
        node->right = AddInternal(node->right, data);
    }

    return DoBalance(node);
}

template<typename T, typename CompareRule>
size_t AvlTree<T, CompareRule>::GetHeight(Node<T> *node) {
    return node ? node->height : 0;
}

template<typename T, typename CompareRule>
void AvlTree<T, CompareRule>::FixHeight(Node<T> *node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::RotateLeft(Node<T> *node) {
    Node<T> *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    FixHeight(node);
    FixHeight(tmp);
    return tmp;
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::RotateRight(Node<T> *node) {
    Node<T> *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    FixHeight(node);
    FixHeight(tmp);
    return tmp;
}

template<typename T, typename CompareRule>
int AvlTree<T, CompareRule>::GetBalance(Node<T> *node) {
    return GetHeight(node->right) - GetHeight(node->left);
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::DoBalance(Node<T> *node) {
    FixHeight(node);

    switch (GetBalance(node)) {
        case 2: {
            if (GetBalance(node->right) < 0) {
                node->right = RotateRight(node->right);
            }

            return RotateLeft(node);
        }
        case -2: {
            if (GetBalance(node->left) > 0) {
                node->left = RotateLeft(node->left);
            }

            return RotateRight(node);
        }

        default:
            return node;
    }
}

template<typename T, typename CompareRule>
AvlTree<T, CompareRule>::~AvlTree() {
    DestroyTree(root);
}

template<typename T, typename CompareRule>
void AvlTree<T, CompareRule>::Add(const T &data) {
    root = AddInternal(root, data);
}

template<typename T, typename CompareRule>
bool AvlTree<T, CompareRule>::Search(const T &data) {
    Node<T> *tmp = root;

    while (tmp) {
        if (tmp->data == data) {
            return true;
        } else if (tmp->data < data) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }

    return false;
}

template<typename T, typename CompareRule>
void AvlTree<T, CompareRule>::Delete(const T &data) {
    root = DeleteInternal(root, data);
}

template<typename T, typename CompareRule>
T AvlTree<T, CompareRule>::SearchNext(const T &data) {
    Node<T> *tmp = root;

    T next_min = 0;

    while (tmp) {
        if (tmp->data < data) {
            tmp = tmp->right;
        } else {
            next_min = tmp->data;
            tmp = tmp->left;
        }
    }

    return next_min;
}

template<typename T, typename CompareRule>
T AvlTree<T, CompareRule>::SearchPrev(const T &data) {
    Node<T> *tmp = root;

    T prev_max = 0;

    while (tmp) {
        if (tmp->data < data) {
            prev_max = tmp->data;
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }

    return prev_max;
}

int main() {
    AvlTree<size_t> avlTree;

    std::string op;
    size_t data;
    while (std::cin >> op >> data) {
        if (op == "insert") {
            avlTree.Add(data);
        }

        if (op == "delete") {
            avlTree.Delete(data);
        }

        if (op == "exists") {
            std::cout << (avlTree.Search(data) ? "true" : "false") << std::endl;
        }

        if (op == "next") {
            int res = avlTree.SearchNext(data);
            if (res) {
                std::cout << res << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        }

        if (op == "prev") {
            int res = avlTree.SearchPrev(data);
            if (res) {
                std::cout << res << std::endl;
            } else {
                std::cout << "none" << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}