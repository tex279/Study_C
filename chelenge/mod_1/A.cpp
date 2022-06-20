#include <stdio.h>
#include <iostream>
#include <cassert>

#define MAX_NUMBER (2e32 - 1)

size_t binary_search(const int key, const int* array, size_t left,  size_t right) {
    while (left < right) {
        size_t mid = (left + right) / 2;

        if (key > array[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return right;
}

int *input_array(size_t &count) {
    std::cin >> count;

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
    size_t length = 0;
    int *array = input_array(length);

    int key = 0;

    std::cin >> key;

    std::cout << binary_search(key, array, 0,  length - 1);

    return EXIT_SUCCESS;
}
