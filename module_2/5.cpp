#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <map>
#include <stack>

class BitWriter {
    std::vector<unsigned char> buffer;
    size_t bit_count;

public:
    BitWriter() : bit_count(0) {}

    void WriteBit(unsigned char bit);

    void WriteByte(unsigned char byte);

    void Clear();

    void Remove(const size_t count);

    const std::vector<unsigned char> &GetBuffer() const;

    const size_t GetBitCount() const;

    BitWriter operator+(const BitWriter &other);

    friend std::ostream &operator<<(std::ostream &out, const BitWriter &bw);
};

BitWriter BitWriter::operator+(const BitWriter &other) {
    BitWriter sum;

    size_t free_pos = 8 - bit_count % 8;

//    std::cout << free_pos << std::endl;

    for (auto &data:buffer) {
        sum.buffer.push_back(data);
    }

    sum.bit_count += bit_count;

    for (auto &data:other.buffer) {
        sum.buffer.push_back(data);
    }

    sum.bit_count += other.bit_count;

    for (size_t j = 0; j < other.buffer.size(); ++j) {
        //  std::cout << std::bitset<8>(sum.buffer[buffer.size() + j - 1]) << std::endl;

//        std::cout << std::bitset<8>(sum.buffer[buffer.size() + j]) << std::endl;

        for (size_t i = 0; i < free_pos; ++i) {
            if ((sum.buffer[buffer.size() + j] >> (7 - i)) & 1) {
//                std::cout << "1" << std::endl;

                sum.buffer[buffer.size() + j - 1] |= 1 << (7 - bit_count % 8 - i);
//
//                std::cout << std::bitset<8>(sum.buffer[buffer.size() + j - 1]) << " " << 7 - bit_count % 8 - i << std::endl;
            }
        }

        sum.buffer[buffer.size() + j] = sum.buffer[buffer.size() + j] << (free_pos);
    }

//    buffer[bit_count / 8] |= 1 << (7 - bit_count % 8);

    if (8 - bit_count % 8 >= other.bit_count % 8) {
        sum.buffer.pop_back();
    }

    return sum;
}

void BitWriter::Clear() {
    buffer.clear();
    bit_count = 0;
}

void BitWriter::Remove(const size_t count) {
    if (count > bit_count) {
        Clear();

        return;
    }

    for (size_t i = 0; i < count; ++i) {
        --bit_count;

        buffer[bit_count / 8] = (buffer[bit_count / 8] >> 8 - bit_count % 8) << 8 - bit_count % 8;
    }

}

std::ostream &operator<<(std::ostream &out, const BitWriter &bw) {
    if (!bw.bit_count) {
        return out;
    }

    for (auto &byte: bw.GetBuffer()) {
        out << std::bitset<8>(byte)  << "|";
    }

    out << bw.bit_count;

    return out;
}

const size_t BitWriter::GetBitCount() const {
    return bit_count;
}

const std::vector<unsigned char> &BitWriter::GetBuffer() const {
    return buffer;
}

void BitWriter::WriteBit(unsigned char bit) {
    if (bit_count == buffer.size() * 8) {
        buffer.push_back(0);
    }

    if (bit) {
        buffer[bit_count / 8] |= 1 << (7 - bit_count % 8);
    }

    ++bit_count;
}

void BitWriter::WriteByte(unsigned char byte) {
    if (bit_count % 8 == 0) {
        buffer.push_back(byte);
    } else {
        size_t offset = bit_count % 8;
        buffer[bit_count / 8] |= byte >> offset;
        buffer.push_back(byte << (8 - offset));
    }

    bit_count += 8;
}

//----------------------------------------------------------------------------------------------------------------------

template<typename T = unsigned char>
struct NodeABS {
    T data;
    size_t freq;

    NodeABS *left;
    NodeABS *right;

    NodeABS(const unsigned char &data, size_t freq = 1) : data(data), freq(freq), left(nullptr), right(nullptr) {}

    friend std::ostream &operator<<(std::ostream &os, const NodeABS &it) {
        return os << it.data << " " << it.freq << std::endl;
    }
};

auto FuncCompare = [](NodeABS<unsigned char> *first, NodeABS<unsigned char> *second) -> bool {
    return first->freq > second->freq;
};

template<typename T>
class BinaryTreeHuffman {
    NodeABS<T> *root;

    std::map<T, BitWriter> table_code;

    BitWriter ser_tree;

    void TraverseCreateSer(NodeABS<T>* node);

    void CreateTable(NodeABS<T>* node, BitWriter bw);

public:
    void Print() const;
    auto GetSerTree();

    auto GetTableCode();

    BinaryTreeHuffman() : root(nullptr) {};
    BinaryTreeHuffman(std::priority_queue < NodeABS<T>*, std::vector <NodeABS<T>*>, decltype(FuncCompare) > min_heap);

    ~BinaryTreeHuffman();
};

template<typename T>
auto BinaryTreeHuffman<T>::GetTableCode() {
    BitWriter bw;
    CreateTable(root, bw);

    return table_code;
}

template<typename T>
void BinaryTreeHuffman<T>::CreateTable(NodeABS<T>* node, BitWriter bw) {
    if (node->data) {
        table_code.insert({node->data, bw});
    } else {
        if (node->left) {
            bw.WriteBit(0);
            CreateTable(node->left, bw);
            bw.Remove(1);
        }

        if (node->right) {
            bw.WriteBit(1);
            CreateTable(node->right, bw);
        }
    }
}

template<typename T>
void BinaryTreeHuffman<T>::TraverseCreateSer(NodeABS<T>* node) {
    if (node->data) {
        ser_tree.WriteBit(1);
        ser_tree.WriteByte(node->data);
    } else {
        TraverseCreateSer(node->left);
        TraverseCreateSer(node->right);
        ser_tree.WriteBit(0);
    }
}

template<typename T>
auto BinaryTreeHuffman<T>::GetSerTree() {
    TraverseCreateSer(root);

    return ser_tree;
}

template<typename T>
BinaryTreeHuffman<T>::BinaryTreeHuffman(std::priority_queue < NodeABS<T>*, std::vector <NodeABS<T>*>, decltype(FuncCompare) > min_heap) {
    while (min_heap.size() > 1) {
        NodeABS<unsigned char> *left = min_heap.top();
        min_heap.pop();

        NodeABS<unsigned char> *right = min_heap.top();
        min_heap.pop();

        NodeABS<unsigned char> *new_node = new NodeABS<unsigned char>({}, left->freq + right->freq);

        new_node->left = left;
        new_node->right = right;

        min_heap.push(new_node);
    }

    root = min_heap.top();
    min_heap.pop();
}

template<typename T>
BinaryTreeHuffman<T>::~BinaryTreeHuffman() {
    std::stack < NodeABS<T> * > s;

    s.push(root);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        delete tmp;

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

template<typename T>
void BinaryTreeHuffman<T>::Print() const {
    std::stack < NodeABS<T> * > s;

    s.push(root);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        std::cout << *tmp;

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}



//----------------------------------------------------------------------------------------------------------------------

void CheckInput(auto &input, auto &input_buffer, auto &min_heap) {
    std::map<unsigned char, size_t> mapABS;

    for (auto data: input) {
        auto needed_node = mapABS.find(data);

        if (needed_node == mapABS.end()) {
            mapABS.insert({data, 1});
        } else {
            needed_node->second++;
        }

        input_buffer.push_back(data);
    }

    CreateHeap(mapABS, min_heap);
}

void CreateHeap(auto &map, auto &min_heap) {
    for (auto &data: map) {
        NodeABS<unsigned char> *node = new NodeABS<unsigned char>(data.first, data.second);
        min_heap.push(node);
    }
}

//----------------------------------------------------------------------------------------------------------------------

void CustomEncode(auto &original, auto &compressed) {
    std::vector<unsigned char> input_buffer;

    std::priority_queue < NodeABS<unsigned char>*, std::vector <NodeABS<unsigned char>*>, decltype(FuncCompare) > min_heap;

    CheckInput(original, input_buffer, min_heap);

    BinaryTreeHuffman<unsigned char> tree_huffman(min_heap);

    auto table = tree_huffman.GetTableCode();

    auto ser = tree_huffman.GetSerTree();

    BitWriter count_ABS;

    count_ABS.WriteByte(table.size());


//    tree_huffman.Print();
//
//    for (auto &data: table) {
//        std::cout << data.first << " " << data.second << std::endl;
//    }
//    std::cout << count_ABS << std::endl;
//
//    std::cout << ser << std::endl;
}

void CustomDecode(auto &compressed, auto &original) {
}

void run(std::istream &input, std::ostream &output) {
    unsigned char tmp;
    std::vector<unsigned char> input_v;
    while (input >> tmp) {
        input_v.push_back(tmp);
    }

    std::vector<unsigned char> compressed;

    CustomEncode(input_v, compressed);
}


int main() {
    //  run(std::cin, std::cout);

    BitWriter bw;

    bw.WriteBit(1);
    bw.WriteBit(0);
    bw.WriteBit(1);
    bw.WriteByte(0);
    bw.WriteBit(1);

    std::cout << bw << std::endl;

    BitWriter bw1;

    bw1.WriteByte(0);
    bw1.WriteBit(1);
    bw1.WriteBit(1);
    bw1.WriteBit(1);
    bw1.WriteBit(1);
    bw1.WriteBit(0);
    bw1.WriteBit(0);
    bw1.WriteBit(1);

    std::cout << bw1 << std::endl;

    BitWriter res = bw + bw1;

    std::cout << res << std::endl;

    BitWriter bw2;

    bw2.WriteBit(1);
    bw2.WriteBit(0);
    bw2.WriteBit(1);

    res = res + bw2;

    std::cout << res << std::endl;

    return EXIT_SUCCESS;
}
