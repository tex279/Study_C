#include <iostream>
#include <vector>

//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
//Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. Начальный
//размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
//когда коэффициент заполнения таблицы достигает B_tree.txt/AVL_tree.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества
//и проверки принадлежности данной строки множеству.
//
//Вариант shortest_path_root_list. Для разрешения коллизий используйте двойное хеширование.

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
    return hasher(str, 71) + (2 * hasher(str, 137) + 1) * iteration;
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


    void Resize(const size_t grow);

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

        os << "size - " << it.size << " capacity - " << it.table.size() << std::endl;

        return os;
    }
};

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::IsFull() const {
    return size == table.size() * MAX_ALPHA;
}

template<typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T &key) {
    if (IsFull()) {
        Resize(2);
    }

    ssize_t pos_DEL = -1;
    for (size_t i = 0; i < table.size(); ++i) {
        size_t hash = probing(key, i) % table.size();

        if (table[hash].data == key) {
            return false;
        }

        if (pos_DEL == -1 && table[hash].status == DEL) {
            pos_DEL = hash;

            continue;
        }

        if (table[hash].status == NIL) {
            if (pos_DEL == -1) {
                table[hash].data = key;
                table[hash].status = KEY;
            } else {
                table[pos_DEL].data = key;
                table[pos_DEL].status = KEY;
            }

            ++size;

            return true;
        }
    }

    table[pos_DEL].data = key;
    table[pos_DEL].status = KEY;

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

        if (table[hash].data == key) {
            return true;
        }

        if (table[hash].status == NIL) {
            return false;
        }
    }

    return false;
}

template<typename T, typename Hasher>
void HashTable<T, Hasher>::Resize(const size_t grow) {
    std::vector <HashTableNode<T>> new_table(table.size() * grow);

    for (auto &value: table) {
        if (value.status == KEY) {
            for (size_t i = 0; i < new_table.size(); ++i) {
                size_t new_hash = probing(value.data, i) % new_table.size();

                if (new_table[new_hash].status == NIL) {
                    new_table[new_hash] = value;

                    break;
                }
            }
        }
    }

    table = std::move(new_table);
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
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
