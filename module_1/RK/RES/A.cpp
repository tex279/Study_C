#include <iostream>

struct Array {
    int* values;
    size_t size;

    Array(size_t init_size);
    ~Array() {delete[] values;}
    Array(const Array&) = delete;

    bool is_empty() {return size == 0;}
};

Array::Array(size_t init_size = 0) {
    values = nullptr;
    size = init_size;
    if (size) {
        values = new int[init_size];
    }
}

int input_data(Array &a) {
    size_t tmp_size;
    std::cin >> tmp_size;

    a.size = tmp_size;
    if (!a.values) {
        a.values = new int[a.size];
    }

    int tmp;
    for (size_t i = 0; i < a.size; ++i) {
        std::cin >> tmp;
        a.values[i] = tmp;
    }

    int find_position;
    std::cin >> find_position;
    return find_position;

}

size_t search_pos_insert(const Array &array, size_t left, size_t right, int x_value) {
    while (left < right) {
        size_t mid = (left + right) / 2;
        (x_value > array.values[mid]) ? left = mid + 1 : right = mid;
    }
    return right;
}


void print_output(const int output) {
    std::cout << output;
}

int main() {
    Array a;
    int find_position = input_data(a);

    int result = search_pos_insert(a, 0, a.size, find_position);

    print_output(result);
    return 0;
}
