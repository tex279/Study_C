#include <iostream>
#include <vector>


const size_t INITIAL_CAPACITY = 8;

const double MAX_ALPHA = 3.0 / 4.0;


class StringHasher {
    size_t prime;

public:
    StringHasher(size_t prime = 71) : prime(prime) {};

    size_t operator()(const std::string &str);
};

size_t StringHasher::operator()(const std::string &str) {
    size_t hash = 0;

    for (auto &ch : str) {
        hash = hash * prime + ch;
    }

    return hash;
}


template<typename T>
struct HashTableNode {
    T data;
    HashTableNode<T> *next;

    HashTableNode() : next(nullptr) {};

    HashTableNode(const T &data, HashTableNode<T> *next) : data(data), next(next) {};

    ~HashTableNode() = default;
};

template<typename T, typename Hasher>
class HashTable {
    std::vector<HashTableNode<T> *> table;

    Hasher hasher;

    size_t size;

    void Resize();

public:
    bool IsFull() const;

    bool Add(const T &key);

    bool Delete(const T &key);

    bool Search(const T &key);

    HashTable(const size_t initial_capacity = INITIAL_CAPACITY) : table(initial_capacity, nullptr), size(0) {};

    ~HashTable();
};

template<typename T, typename Hasher>
HashTable<T, Hasher>::~HashTable() {
    for (auto &value : table) {
        HashTableNode<T> *node = value;

        while (node) {
            HashTableNode<T> *next = node->next;

            delete node;

            node = next;
        }
    }
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::IsFull() const {
    return size == table.size() * MAX_ALPHA;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T &key) {
    if (IsFull()) {
        Resize();
    }

    size_t hash = hasher(key) % table.size();

    HashTableNode<T> *node = table[hash];
    while (node) {
        if (node->data == key) {
            return false;
        }

        node = node->next;
    }

    table[hash] = new HashTableNode<T>(key, table[hash]);

    ++size;

    return true;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::Delete(const T &key) {
    size_t hash = hasher(key) % table.size();

    HashTableNode<T> *node = table[hash];

    HashTableNode<T> *prev = nullptr;
    while (node) {
        if (node->data == key) {
            break;
        }
        prev = node;

        node = node->next;
    }

    if (!node) {
        return false;
    }

    if (!prev) {
        table[hash] = node->next;
    } else {
        prev->next = node->next;
    }

    delete node;

    size--;

    return true;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::Search(const T &key) {
    size_t hash = hasher(key) % table.size();

    HashTableNode<T> *node = table[hash];
    while (node) {
        if (node->data == key) {
            return true;
        }

        node = node->next;
    }

    return false;
}

template<typename T, typename Hasher>
void HashTable<T, Hasher>::Resize() {
    std::vector < HashTableNode<T> * > new_table(this->table.size() * 2, nullptr);

    for (auto &value : table) {
        HashTableNode<T> *node = value;

        while (node) {
            HashTableNode<T> *next = node->next;

            size_t new_hash = hasher(node->data) % new_table.size();

            node->next = new_table[new_hash];

            new_table[new_hash] = node;

            node = next;
        }
    }

    table = std::move(new_table);
}

void run(std::istream &input, std::ostream &output) {
    HashTable<std::string, StringHasher> hash_table;

    char op;

    std::string key;

    while (input >> op >> key) {
        switch (op) {
            case '+': {
                output << (hash_table.Add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }

            case '-': {
                output << (hash_table.Delete(key) ? "OK" : "FAIL") << std::endl;
                break;
            }

            case '?': {
                output << (hash_table.Search(key) ? "OK" : "FAIL") << std::endl;
                break;
            }

            default: {
                break;
            }
        }
    }
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
