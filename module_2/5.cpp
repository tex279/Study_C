#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <map>
#include <stack>

using byte = u_int8_t;

template<typename T = byte>
struct NodeABS {
    T data;
    size_t freq;

    NodeABS *left;
    NodeABS *right;

    NodeABS(const T &data, size_t freq = 1) : data(data), freq(freq), left(nullptr), right(nullptr) {}

    friend std::ostream &operator<<(std::ostream &os, const NodeABS &it) {
        return os << it.data << " " << it.freq << std::endl;
    }
};

//----------------------------------------------------------------------------------------------------------------------

class BitReader {
    std::vector <byte> buffer;

    size_t free_bit;

    size_t count_ABS;
public:
    BitReader(std::vector <byte> buffer) : buffer(buffer) {
        free_bit = buffer[0];
        count_ABS = buffer[1];
    }

    BitReader() = default;

    size_t GetFreeBits() const;

    size_t GetTree(NodeABS<byte> *&root) const;

    void GetDecodeDataZeroFreeBit(const size_t start_pos, NodeABS<byte> *root,
                                  std::vector <byte> &decode) const;

    void GetDecodeDataNonNullFreeBit(const size_t start_pos, NodeABS<byte> *root,
                                     std::vector <byte> &decode) const;

    const std::vector <byte> &GetBuffer() const;

    friend std::ostream &operator<<(std::ostream &out, const BitReader &br);
};

void BitReader::GetDecodeDataZeroFreeBit(const size_t start_pos, NodeABS<byte> *root, std::vector <byte> &decode) const {
    NodeABS<byte> **cur = &root;

    size_t i = start_pos;

    while (true) {
        NodeABS<byte> &node = **cur;

        if (!node.right && !node.left) {
            decode.push_back(node.data);

            cur = &root;

            continue;
        }

        if (i % 8 == free_bit && i / 8 == buffer.size()) {
            break;
        }

        if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
            cur = &node.right;
            ++i;
        } else {
            cur = &node.left;
            ++i;
        }
    }
}

void
BitReader::GetDecodeDataNonNullFreeBit(const size_t start_pos, NodeABS<byte> *root, std::vector <byte> &decode) const {
    NodeABS<byte> **cur = &root;

    size_t i = start_pos;

    while (true) {
        NodeABS<byte> &node = **cur;

        if (!node.right && !node.left) {
            decode.push_back(node.data);

            cur = &root;

            continue;
        }

        if (i % 8 == 8 - free_bit && i / 8 == buffer.size() - 1) {
            break;
        }

        if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
            cur = &node.right;
        } else {
            cur = &node.left;
        }

        ++i;
    }
}


size_t BitReader::GetTree(NodeABS<byte> *&root) const {
    if (free_bit == 255) {
        root = nullptr;
        return 0;
    }

    std::stack < NodeABS<byte> * > s;

    size_t i = 8 * 2;

    size_t count_read_abs = 0;
    while (count_read_abs < count_ABS || s.size() > 1) {
        if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
            ++i;

            NodeABS<byte> *new_node = new NodeABS<byte>({});

            for (size_t j = 0; j < 8; ++j) {
                if ((buffer[i / 8] >> (7 - i % 8)) & 1) {
                    new_node->data |= 1 << (7 - j % 8);
                }

                ++i;
            }

            s.push(new_node);

            ++count_read_abs;
        } else {
            ++i;

            NodeABS<byte> *right = s.top();
            s.pop();

            NodeABS<byte> *left = s.top();
            s.pop();

            NodeABS<byte> *new_node = new NodeABS<byte>({});

            new_node->left = left;
            new_node->right = right;

            s.push(new_node);
        }
    }

    root = s.top();

    return i;
}

const std::vector <byte> &BitReader::GetBuffer() const {
    return buffer;
}

size_t BitReader::GetFreeBits() const {
    return free_bit;
}

std::ostream &operator<<(std::ostream &out, const BitReader &br) {
    for (auto &byte: br.GetBuffer()) {
        out << std::bitset<8>(byte) << "|";
    }

    out << "Count bytes " << br.GetBuffer().size();

    return out;
}

//----------------------------------------------------------------------------------------------------------------------

class BitWriter {
    std::vector <byte> buffer;

    size_t bit_count;
public:
    BitWriter() : bit_count(0) {}

    void WriteBit(byte bit);

    void WriteByte(byte byte);

    void Remove(const size_t count);

    size_t GetFreeBits() const;

    const std::vector <byte> &GetBuffer() const;

    const size_t GetBitCount() const;

    BitWriter &operator+=(const BitWriter &other);

    friend std::ostream &operator<<(std::ostream &out, const BitWriter &bw);
};

size_t BitWriter::GetFreeBits() const {
    size_t free_bit = 8 - bit_count % 8;
    if (free_bit == 8) {
        return 0;
    } else {
        return free_bit;
    }
}

BitWriter &BitWriter::operator+=(const BitWriter &other) {
    size_t free_pos_left = 8 - bit_count % 8;

    size_t free_pos_right = 8 - other.bit_count % 8;

    size_t start_size = buffer.size();

    for (auto &data: other.buffer) {
        buffer.push_back(data);
    }

    if (free_pos_left != 8) {
        for (size_t j = 0; j < other.buffer.size(); ++j) {
            for (size_t i = 0; i < free_pos_left; ++i) {
                if ((buffer[start_size + j] >> (7 - i)) & 1) {
                    buffer[start_size + j - 1] |= 1 << (7 - bit_count % 8 - i);
                }
            }

            buffer[start_size + j] = buffer[start_size + j] << (free_pos_left);
        }

        if (free_pos_left % 8 < 8 && free_pos_right < 8) {
            if (free_pos_left >= other.bit_count % 8) {
                buffer.pop_back();
            }
        }
    }

    bit_count += other.bit_count;

    return *this;
}

void BitWriter::Remove(const size_t count) {
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
        out << std::bitset<8>(byte) << "|";
    }

    out << bw.bit_count;

    return out;
}

const size_t BitWriter::GetBitCount() const {
    return bit_count;
}

const std::vector <byte> &BitWriter::GetBuffer() const {
    return buffer;
}

void BitWriter::WriteBit(byte bit) {
    if (bit_count == buffer.size() * 8) {
        buffer.push_back(0);
    }

    if (bit) {
        buffer[bit_count / 8] |= 1 << (7 - bit_count % 8);
    }

    ++bit_count;
}

void BitWriter::WriteByte(byte byte) {
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

template<typename T>
class More {
public:
    bool operator()(const NodeABS<T> *first, const NodeABS<T> *second) const {
        return first->freq > second->freq;
    }
};

const More<unsigned char> more;

template<typename T>
class BinaryTreeHuffman {
    NodeABS<T> *root;

    std::map <T, BitWriter> table_code;

    BitWriter ser_tree;

    BitReader decode;
    size_t pos_start;

    size_t free_pos_bits;

    std::vector <T> res;

    void TraverseCreateSer(NodeABS<T> *node);

    void CreateTable(NodeABS<T> *node, BitWriter bw);

public:
    auto GetRoot() const { return root; }

    void Print() const;

    auto GetSerTree();

    auto GetTableCode();

    auto GetDecode();

    BinaryTreeHuffman() : root(nullptr) {};

    BinaryTreeHuffman(std::priority_queue<NodeABS<T> *, std::vector < NodeABS<T> * >, decltype(more)> min_heap);

    BinaryTreeHuffman(BitReader &compressed);

    ~BinaryTreeHuffman();
};

template<typename T>
auto BinaryTreeHuffman<T>::GetDecode() {
    if (decode.GetFreeBits() == 0) {
        decode.GetDecodeDataZeroFreeBit(pos_start, root, res);
    } else {
        decode.GetDecodeDataNonNullFreeBit(pos_start, root, res);
    }

    return res;
}

template<typename T>
BinaryTreeHuffman<T>::BinaryTreeHuffman(BitReader &compressed) {
    pos_start = compressed.GetTree(root);

    decode = compressed;
}

template<typename T>
auto BinaryTreeHuffman<T>::GetTableCode() {
    BitWriter bw;
    CreateTable(root, bw);

    return table_code;
}

template<typename T>
void BinaryTreeHuffman<T>::CreateTable(NodeABS<T> *node, BitWriter bw) {
    if (!node->left && !node->left) {
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
void BinaryTreeHuffman<T>::TraverseCreateSer(NodeABS<T> *node) {
    if (!node->left && !node->right) {
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
    if (ser_tree.GetBuffer().empty()) {
        TraverseCreateSer(root);
    }

    return ser_tree;
}

template<typename T>
BinaryTreeHuffman<T>::BinaryTreeHuffman(std::priority_queue < NodeABS<T> * , std::vector < NodeABS<T> * > ,
                                        decltype(more) > min_heap) {
    while (min_heap.size() > 1) {
        NodeABS<T> *left = min_heap.top();
        min_heap.pop();

        NodeABS<T> *right = min_heap.top();
        min_heap.pop();

        NodeABS<T> *new_node = new NodeABS<byte>({}, left->freq + right->freq);

        new_node->left = left;
        new_node->right = right;

        min_heap.push(new_node);
    }

    root = min_heap.top();

    min_heap.pop();
}

template<typename T>
BinaryTreeHuffman<T>::~BinaryTreeHuffman() {
    if (!root) {
        return;
    }

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
    std::map <byte, size_t> mapABS;

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
        NodeABS<byte> *node = new NodeABS<byte>(data.first, data.second);

        min_heap.push(node);
    }
}

//----------------------------------------------------------------------------------------------------------------------

void CustomEncode(auto &original, auto &compressed) {
    std::vector <byte> input_buffer;

    std::priority_queue < NodeABS<byte> * , std::vector < NodeABS<byte> * >, decltype(more) > min_heap;

    CheckInput(original, input_buffer, min_heap);

    BinaryTreeHuffman<byte> tree_huffman_encode(min_heap);

    auto table = tree_huffman_encode.GetTableCode();

    if (table.empty()) {
        compressed = original;
        return;
    }

    BitWriter begin;

    if (table.size() < 256) {
        begin.WriteByte(table.size());
    } else {
        begin.WriteByte(table.size() - 1);
    }

    begin += tree_huffman_encode.GetSerTree();

    BitWriter code;

    for (auto &data: input_buffer) {
        auto needed_node = table.find(data);
        begin += needed_node->second;

        code += needed_node->second;
    }

    BitWriter result;

    result.WriteByte(begin.GetFreeBits());

    result += begin;

    compressed = result.GetBuffer();

    if (compressed.size() > original.size()) {

        std::vector <byte> null_compress;

        null_compress.push_back(255);

        for (auto &data: original) {
            null_compress.push_back(data);
        }

        compressed = null_compress;
    }

//    std::cout << "TREE" << std::endl;
//    tree_huffman_encode.Print();
//    std::cout << "TABLE" << std::endl;
//    for (auto &data: table) {
//        std::cout << data.first << " " << data.second << std::endl;
//    }
//    std::cout << "TABLE SIZE - " << table.size() << std::endl;
//    std::cout << "SER - " << tree_huffman_encode.GetSerTree() << std::endl;
//    std::cout << "CODE - " << code << std::endl;
//    std::cout << "FREE BITS - " << begin.GetFreeBits() << std::endl;
//    std::cout << result << std::endl;
}

void CustomDecode(auto &compressed, auto &original) {
    BitReader br(compressed);

    BinaryTreeHuffman<byte> tree_huffman_decode(br);


    if (!tree_huffman_decode.GetRoot()) {
        for (size_t i = 1; i < compressed.size(); ++i) {
            original.push_back(compressed[i]);
        }

        compressed.erase(compressed.begin());

        return;
    }

    auto res = tree_huffman_decode.GetDecode();

    original = res;
}

void AnalysisCompress(auto input_data, auto &compressed, auto &expected_data) {
    std::cout << "Size before compress: " << input_data.size() << " bytes" << std::endl;
    std::cout << "After compress: " << compressed.size() << " bytes" << std::endl;

    std::cout << "Compression ratio - " << (double) compressed.size() / (double) input_data.size() << std::endl;

    if (input_data == expected_data) {
        std::cout << "SUCCESS" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }
}

void run(std::istream &input, std::ostream &output) {
    byte tmp;

    std::vector <byte> input_v;

    while (input >> std::noskipws >> tmp) {
        input_v.push_back(tmp);
    }

    if (input_v.empty()) {
        std::cout << "Null input" << std::endl;

        return;
    }

    std::vector <byte> compressed;

    CustomEncode(input_v, compressed);

    std::vector <byte> expected_data;

    CustomDecode(compressed, expected_data);

    AnalysisCompress(input_v, compressed, expected_data);
}

int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
