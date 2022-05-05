#include <iostream>
#include <vector>


const size_t INITIAL_CAPACITY = 8;

const double MAX_ALPHA = 3.0 / 4.0;

enum  status_node {NIL = 0, KEY, DEL};


class StringHasher {
public:
    StringHasher() = default;
    ~StringHasher() = default;

    size_t operator()(const std::string &str, const size_t prime);
};

size_t StringHasher::operator()(const std::string &str, const size_t prime) {
    size_t hash = 0;

    for (auto &ch: str) {
        hash = hash * prime + ch;
    }

    return hash;
}

template<typename Hasher>
class DoubleHashProbing {
  Hasher hasher;
public:
    size_t operator()(const std::string &str, const size_t iteration);
};

template<typename Hasher>
size_t DoubleHashProbing<Hasher>::operator()(const std::string &str, const size_t iteration) {
    return hasher(str, 71) + hasher(str, 43) * iteration;
}


template<typename T>
struct HashTableNode {
    T data;

    status_node status;

    HashTableNode() : status(NIL) {};

    HashTableNode(const T &data) : data(data), status(KEY) {};

    ~HashTableNode() = default;

    friend std::ostream& operator<<(std::ostream &os, const HashTableNode<T> &it)  {
        return os << it.data << " " << it.status << std::endl;
    }
};

template<typename T, typename Probing>
class HashTable {
    std::vector<HashTableNode<T>> table;

    Probing probing;

    size_t size;

    void Resize();

public:
    bool IsFull() const;

    bool Add(const T &key);

    bool Delete(const T &key);

    bool Search(const T &key);

    HashTable(const size_t initial_capacity = INITIAL_CAPACITY) : table(initial_capacity), size(0) {};
    ~HashTable() = default;

    friend std::ostream& operator<<(std::ostream &os, const HashTable<T, Probing> &it)  {
        for (auto &value : it.table) {
            os << value.data << " " << value.status << std::endl;
        }

        os << it.size << " " << it.table.size() << std::endl;

        return os;
    }
};

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::IsFull() const {
    //  std::cout << size << "!!!! !!!!" << table.size() << std::endl;
    return size >= table.size() * MAX_ALPHA;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T &key) {
    if (IsFull()) {
        //  std::cout << size << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << table.size() << std::endl;
        Resize();
    }

    ssize_t pos_DEL = -1;
    for (size_t i = 0; i < table.size(); ++i) {
        size_t hash = probing(key, i) % table.size();

        if (pos_DEL == -1 && table[hash].status == DEL) {
            pos_DEL = hash;
        }

        if (table[hash].status == NIL) {
            if (pos_DEL != -1) {
                table[pos_DEL].data = key;
                table[pos_DEL].status = KEY;
            } else {
                table[hash].data = key;
                table[hash].status = KEY;
            }

            ++size;

            return true;
        }

        if (table[hash].data == key) {
            return false;
        }
    }

    table[pos_DEL].data = key;

    ++size;

    return true;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::Delete(const T &key) {
    for (size_t i = 0; i < table.size(); ++i) {
        size_t hash = probing(key, i) % table.size();

        if (table[hash].status == NIL) {
            return false;
        }

        if (table[hash].data == key) {
            table[hash].data = {};

            table[hash].status = DEL;

            --size;

            return true;
        }
    }

    return false;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::Search(const T &key) {
    for (size_t i = 0; i < table.size(); ++i) {
        size_t hash = probing(key, i) % table.size();

        if (table[hash].status == NIL) {
            return false;
        }

        if (table[hash].data == key) {
            return true;
        }
    }

    return false;
}

template<typename T, typename Hasher>
void HashTable<T, Hasher>::Resize() {
    std::vector <HashTableNode<T>> new_table(this->table.size() * 2);

    std::vector <HashTableNode<T>> buf = std::move(table);

    table = std::move(new_table);

    for (auto &value: buf) {
        if (value.status == KEY) {
            Add(value.data);
        }
    }
}


void run(std::istream &input, std::ostream &output) {
    HashTable<std::string, DoubleHashProbing<StringHasher>> hash_table;

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

    output << hash_table << std::endl;
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
