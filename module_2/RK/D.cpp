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
class AvlTree {
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

template<typename T>
void AvlTree<T>::DestroyTree(Node<T> *node) {
    if (node) {
        DestroyTree(node->left);
        DestroyTree(node->right);

        delete node;
    }
}

template<typename T>
Node<T> *AvlTree<T>::DeleteInternal(Node<T> *node, const T &data) {
    if (!node) {
        return nullptr;
    }

    if (node->data < data) {
        node->right = DeleteInternal(node->right, data);
    } else if (node->data > data) {
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

template<typename T>
Node<T> *AvlTree<T>::FindMin(Node<T> *node) {
    while (node->left)
        node = node->left;
    return node;
}

template<typename T>
Node<T> *AvlTree<T>::RemoveMin(Node<T> *node) {
    if (!node->left) {
        return node->right;
    }

    node->left = RemoveMin(node->left);

    return DoBalance(node);
}

template<typename T>
Node<T> *AvlTree<T>::AddInternal(Node<T> *node, const T &data) {
    if (!node) {
        return new Node(data);
    }

    if (node->data <= data) {
        node->right = AddInternal(node->right, data);
    } else {
        node->left = AddInternal(node->left, data);
    }

    return DoBalance(node);
}

template<typename T>
size_t AvlTree<T>::GetHeight(Node<T> *node) {
    return node ? node->height : 0;
}

template<typename T>
void AvlTree<T>::FixHeight(Node<T> *node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

template<typename T>
Node<T> *AvlTree<T>::RotateLeft(Node<T> *node) {
    Node<T> *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    FixHeight(node);
    FixHeight(tmp);
    return tmp;
}

template<typename T>
Node<T> *AvlTree<T>::RotateRight(Node<T> *node) {
    Node<T> *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    FixHeight(node);
    FixHeight(tmp);
    return tmp;
}

template<typename T>
int AvlTree<T>::GetBalance(Node<T> *node) {
    return GetHeight(node->right) - GetHeight(node->left);
}

template<typename T>
Node<T> *AvlTree<T>::DoBalance(Node<T> *node) {
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

template<typename T>
AvlTree<T>::~AvlTree() {
    DestroyTree(root);
}

template<typename T>
void AvlTree<T>::Add(const T &data) {
    root = AddInternal(root, data);
}

template<typename T>
bool AvlTree<T>::Search(const T &data) {
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

template<typename T>
void AvlTree<T>::Delete(const T &data) {
    root = DeleteInternal(root, data);
}

template<typename T>
T AvlTree<T>::SearchNext(const T &data) {
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

template<typename T>
T AvlTree<T>::SearchPrev(const T &data) {
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
    AvlTree<int> avlTree;

    std::string op;
    int data;
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