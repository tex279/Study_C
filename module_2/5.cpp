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
        //buffer[bit_count / 8] |= 0 << (7 - bit_count % 8);

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
class Less {
public:
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<typename T>
class ActionDefault {
public:
    void operator() (const NodeABS<T>& it) const {}
};

template<typename T, typename CompareRule = Less<T>>
class BinaryTreeHuffman {
    NodeABS<T> *root;

    std::map<T, BitWriter> table_code;

    BitWriter ser_tree;

    std::vector<std::pair<T, size_t>> freq;

    CompareRule rule;

    size_t size;

    BitWriter GetPath(NodeABS<T>* node, BitWriter v, T key) const;
public:
    bool IsEmpty() const;

    void SetFreq();

    auto GetFreq() const;

    NodeABS<T>* Root() const {return root;}

    void TraverseCreateSer(NodeABS<T>* node);
    auto GetSerTree() const;

    void CreateTable();
    auto GetTableCode() const;

    BinaryTreeHuffman() : root(nullptr), size(0) {};
    BinaryTreeHuffman(std::priority_queue < NodeABS<T>*, std::vector <NodeABS<T>*>, decltype(FuncCompare) > min_heap);

    ~BinaryTreeHuffman();

    template<class Action = ActionDefault<T>>
    void PreOrderTree(NodeABS<T>* begin, const Action& act);

    template<class Action = ActionDefault<T>>
    void InOrderTree(NodeABS<T>* begin, const Action& act);

    template<class Action = ActionDefault<T>>
    void PostOrderTree(NodeABS<T>* begin, const Action& act);

    template<class Action = ActionDefault<T>>
    void BFSTree(NodeABS<T>* begin, const Action& act);
};

template<typename T, typename CompareRule>
BitWriter BinaryTreeHuffman<T, CompareRule>::GetPath(NodeABS<T>* node, BitWriter v, T key) const {
    if (!node) {
        return v;
    }

    if (node->data == key) {
        return v;
    } else if (node->left) {
        v.WriteBit(0);
        v = GetPath(node->left, v, key);
    } else {
        v.WriteBit(1);
        v = GetPath(node->right, v, key);
    }

    return v;
}

template<typename T, typename CompareRule>
auto BinaryTreeHuffman<T, CompareRule>::GetTableCode() const {
    return table_code;
}

template<typename T, typename CompareRule>
auto BinaryTreeHuffman<T, CompareRule>::GetFreq() const {
    return freq;
}

template<typename T, typename CompareRule>
void BinaryTreeHuffman<T, CompareRule>::CreateTable() {
    BitWriter bw;
    bw = GetPath(root, bw, 2);

    std::cout << bw;
}

template<typename T, typename CompareRule>
void BinaryTreeHuffman<T, CompareRule>::TraverseCreateSer(NodeABS<T>* node) {
    if (node->data) {
        ser_tree.WriteBit(1);
        ser_tree.WriteByte(node->data);
    } else {
        TraverseCreateSer(node->left);
        TraverseCreateSer(node->right);
        ser_tree.WriteBit(0);
    }
}

template<typename T, typename CompareRule>
auto BinaryTreeHuffman<T, CompareRule>::GetSerTree() const {
    return ser_tree;
}

template<typename T, typename CompareRule>
BinaryTreeHuffman<T, CompareRule>::BinaryTreeHuffman(std::priority_queue < NodeABS<T>*, std::vector <NodeABS<T>*>, decltype(FuncCompare) > min_heap) {
    size_t count_iter = min_heap.size() - 1;

    for (size_t i = 0; i < count_iter; ++i) {
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

template<typename T, typename CompareRule>
BinaryTreeHuffman<T, CompareRule>::~BinaryTreeHuffman() {
    this->PostOrderTree(root, [](NodeABS<T>& it) { delete &it; });
}

template<typename T, typename CompareRule>
bool BinaryTreeHuffman<T, CompareRule>::IsEmpty() const {
    return !size;
}

template<typename T, typename CompareRule>
void BinaryTreeHuffman<T, CompareRule>::SetFreq() {
    if (IsEmpty()) {
        return;
    }

    std::stack < NodeABS<T> * > s;

    s.push(root);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        if (tmp->data) {
            freq.push_back({tmp->data,tmp->freq});
        }

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

template<typename T, typename CompareRule>
template<class Action>
void BinaryTreeHuffman<T, CompareRule>::PreOrderTree(NodeABS<T>* begin, const Action& act) {
    if (IsEmpty()) {
        return;
    }

    std::stack < NodeABS<T> * > s;

    s.push(begin);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        act(*tmp);

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

template<typename T, typename CompareRule>
template<class Action>
void BinaryTreeHuffman<T, CompareRule>::InOrderTree(NodeABS<T>* begin, const Action& act) {
    if (IsEmpty()) {
        return;
    }

    std::stack < NodeABS<T> * > s;

    s.push(begin);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        if (tmp->right) {
            s.push(tmp->right);
        }

        act(*tmp);

        if (tmp->left) {
            s.push(tmp->left);
        }
    }
}

template<typename T, typename CompareRule>
template<class Action>
void BinaryTreeHuffman<T, CompareRule>::PostOrderTree(NodeABS<T>* begin, const Action& act) {
    if (IsEmpty()) {
        return;
    }

    std::stack < NodeABS<T> * > s;

    s.push(begin);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.top();
        s.pop();

        if (tmp->right) {
            s.push(tmp->right);
        }

        if (tmp->left) {
            s.push(tmp->left);
        }

        act(*tmp);
    }
}

template<typename T, typename CompareRule>
template<class Action>
void BinaryTreeHuffman<T, CompareRule>::BFSTree(NodeABS<T>* begin, const Action& act) {
    if (IsEmpty()) {
        return;
    }

    std::queue< NodeABS<T> * > s;

    s.push(begin);

    while (!s.empty()) {
        NodeABS<T> *tmp = s.front();
        s.pop();

        act(*tmp);

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

    tree_huffman.PreOrderTree(tree_huffman.Root(), [](const NodeABS<unsigned char>& it) {  std::cout << it; });

    tree_huffman.TraverseCreateSer(tree_huffman.Root());

    auto ser_tree = tree_huffman.GetSerTree();

    //  std::cout << ser_tree;

    tree_huffman.SetFreq();
    auto freq = tree_huffman.GetFreq();

    for (auto &data: freq) {
        std::cout << data.first << " " << data.second << " ";
    }
    std::cout << std::endl;

    tree_huffman.CreateTable();

    auto table = tree_huffman.GetTableCode();

    for (auto &value: table) {
        std::cout << value.first << " " << value.second << std::endl;
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

//    std::vector<unsigned char> expected_decode;
//
//    CustomDecode(compressed, expected_decode);
//
//    if (input_v == expected_decode) {
//        output << "SUCCESS" << std::endl;
//    } else {
//        output << "ORIGINAL_DATA_ : ";
//        for (auto &data: input_v) {
//            output << data << std::endl;
//        }
//        output << std::endl;
//
//        output << "AFTER_COMPRESS : ";
//        for (auto &data: expected_decode) {
//            output << data << std::endl;
//        }
//        output << std::endl;
//    }
}


int main() {
    run(std::cin, std::cout);

//    BitWriter bw;
//    bw.WriteByte(5);
//
//    std::cout << bw << std::endl;

    return EXIT_SUCCESS;
}


