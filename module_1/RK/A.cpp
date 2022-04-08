#include <stdio.h>
#include <iostream>
#include <cassert>

size_t binary_search(const int key, const int* array, size_t left,  size_t right) {
    if (key < array[left]) {
        return left;
    }

    if (key > array[right]) {
        return right;
    }

    while (left + 1 != right) {
        size_t mid = (left + right) / 2;

        if (array[mid] > key) {
            right = mid;
        } else {
            left = mid;
        }
    }

    if (key - array[left] > array[right] - key) {
        return right;
    } else {
        return left;
    }
}

int *input_array(size_t max_count, size_t &count) {
    std::cin >> count;

    assert(count <= max_count);

    int *res = new int [count];
    if (!res) {
        return nullptr;
    }

    for (size_t i = 0; i < count; ++i) {
        std::cin >> res[i];
    }

    return res;
}

int main() {


    return EXIT_SUCCESS;
}
