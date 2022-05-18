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

    friend std::ostream &operator<<(std::ostream &out, const BitWriter &bw);
};

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
        out << std::bitset<8>(byte) << " " << bw.bit_count << "|";
    }

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
public:
    void Print() const;

    void TraverseCreateSer(NodeABS<T>* node);
    auto GetSerTree() const;

    void CreateTable(NodeABS<T>* node, BitWriter bw);
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
    std::cout << node->freq << std::endl;
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
auto BinaryTreeHuffman<T>::GetSerTree() const {
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

//    while (!min_heap.empty()) {
//        std::cout << *min_heap.top();
//        min_heap.pop();
//    }
}

//----------------------------------------------------------------------------------------------------------------------

void CustomEncode(auto &original, auto &compressed) {
    std::vector<unsigned char> input_buffer;

    std::priority_queue < NodeABS<unsigned char>*, std::vector <NodeABS<unsigned char>*>, decltype(FuncCompare) > min_heap;

    CheckInput(original, input_buffer, min_heap);

    BinaryTreeHuffman<unsigned char> tree_huffman(min_heap);
    tree_huffman.Print();

    auto table = tree_huffman.GetTableCode();

    for (auto &data: table) {
        std::cout << data.first << " " << data.second << std::endl;
    }

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
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
