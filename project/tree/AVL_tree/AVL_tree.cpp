#include <iostream>

//    Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел,
//    а также запрос на получение k-ой порядковой статистики. Команда добавления числа binary_search задается положительным
//    числом binary_search, команда удаления числа binary_search задается отрицательным числом “-binary_search”. Запрос на
//    получение k-ой порядковой статистики задается числом k.
//    Требования: скорость выполнения запроса - O(log n).


template<typename T>
struct Node {
    T data;

    size_t height;

    size_t count;

    Node *left;
    Node *right;

    Node(const T &data) : data(data), height(1), count(1), left(nullptr), right(nullptr) {}
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

    size_t size;

    Node<T> *root;

    void DestroyTree(Node<T> *node);

    Node<T> *DeleteInternal(Node<T> *node, const T &data);
    Node<T> *AddInternal(Node<T> *node, const T &data);

    Node<T> *FindMin(Node<T> *node) const;
    Node<T> *RemoveMin(Node<T> *node);
    Node<T> *FindAndRemoveMin(Node<T> *node);

    Node<T> *FindMax(Node<T> *node) const;
    Node<T> *RemoveMax(Node<T> *node);
    Node<T> *FindAndRemoveMax(Node<T> *node);


    size_t GetHeight(const Node<T> *node) const;
    void FixHeight(Node<T> *node);

    Node<T> *RotateLeft(Node<T> *node);
    Node<T> *RotateRight(Node<T> *node);

    int GetBalance(const Node<T> *node) const;
    Node<T> *DoBalance(Node<T> *node);

    size_t GetCount(const Node<T> *node) const;
    void FixCount(Node<T> *node);

    T GetKStatistsNode(size_t k_stat, const Node<T> *node) const;

public:
    AvlTree() : root(nullptr), size(0) {}

    ~AvlTree();

    void Add(const T &data);

    bool Search(const T &data) const;

    void Delete(const T &data);

    size_t Size() const;

    T GetKStatists(size_t k_stat) const;

};

template<typename T, typename CompareRule>
size_t AvlTree<T, CompareRule>::Size() const {
    return size;
}

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

        Node<T> *new_node_del_pos;

        if (GetHeight(left) > GetHeight(right)) {
            new_node_del_pos = FindAndRemoveMax(left);
            new_node_del_pos->right = right;
        } else {
            new_node_del_pos = FindAndRemoveMin(right);
            new_node_del_pos->left = left;
        }

        --size;

        return DoBalance(new_node_del_pos);
    }

    return DoBalance(node);
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::FindMin(Node<T> *node) const {
    while (node->left) {
        node = node->left;
    }

    return node;
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::FindMax(Node<T> *node) const {
    while (node->right) {
        node = node->right;
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
Node<T> *AvlTree<T, CompareRule>::RemoveMax(Node<T> *node) {
    if (!node->right) {
        return node->left;
    }

    node->right = RemoveMax(node->right);

    return DoBalance(node);
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::FindAndRemoveMin(Node<T> *node) {
    Node<T> *min = FindMin(node);
    min->right = RemoveMin(node);

    return min;
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::FindAndRemoveMax(Node<T> *node) {
    Node<T> *max = FindMax(node);
    max->left = RemoveMax(node);

    return max;
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::AddInternal(Node<T> *node, const T &data) {
    if (!node) {
        ++size;
        return new Node(data);
    }

    if (rule(data, node->data)) {
        node->left = AddInternal(node->left, data);
    } else {
        node->right = AddInternal(node->right, data);
    }

    return DoBalance(node);
}

template<typename T, typename CompareRule>
size_t AvlTree<T, CompareRule>::GetHeight(const Node<T> *node) const {
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
    FixCount(node);
    FixHeight(tmp);
    FixCount(tmp);

    return tmp;
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::RotateRight(Node<T> *node) {
    Node<T> *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    FixHeight(node);
    FixCount(node);
    FixHeight(tmp);
    FixCount(tmp);

    return tmp;
}

template<typename T, typename CompareRule>
int AvlTree<T, CompareRule>::GetBalance(const Node<T> *node) const {
    return GetHeight(node->right) - GetHeight(node->left);
}

template<typename T, typename CompareRule>
Node<T> *AvlTree<T, CompareRule>::DoBalance(Node<T> *node) {
    FixHeight(node);
    FixCount(node);

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
bool AvlTree<T, CompareRule>::Search(const T &data) const {
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
size_t AvlTree<T, CompareRule>::GetCount(const Node<T> *node) const {
    return node ? node->count : 0;
}

template<typename T, typename CompareRule>
void AvlTree<T, CompareRule>::FixCount(Node<T> *node) {
    node->count = GetCount(node->left) + GetCount(node->right) + 1;
}

template<typename T, typename CompareRule>
T AvlTree<T, CompareRule>::GetKStatistsNode(size_t k_stat, const Node<T> *node) const {
    size_t count_left = GetCount(node->left);

    if (count_left == k_stat) {
        return (node->data);
    } else if (count_left > k_stat) {
        return GetKStatistsNode(k_stat, node->left);
    } else {
        k_stat = k_stat - count_left - 1;

        return GetKStatistsNode(k_stat, node->right);
    }
}

template<typename T, typename CompareRule>
T AvlTree<T, CompareRule>::GetKStatists(size_t k_stat) const {
    return GetKStatistsNode(k_stat, root);
}

void run(std::istream &input, std::ostream &output) {
    AvlTree<size_t> avlTree;

    size_t n;

    input >> n;

    long int tmp;

    size_t k_stat;

    for (size_t i = 0; i < n; ++i) {
        input >> tmp >> k_stat;

        if (tmp >= 0) {
            avlTree.Add((size_t) tmp);
        } else {
            avlTree.Delete(std::abs(tmp));
        }

        output << avlTree.GetKStatists(k_stat) << " ";
    }
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}