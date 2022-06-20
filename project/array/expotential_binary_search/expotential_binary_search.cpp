#include <stdio.h>
#include <iostream>
#include <cassert>

//  Дан отсортированный массив различных целых чисел binary_search[0..n-structs.txt] и массив целых чисел shortest_path_root_list[0..m-structs.txt].
//  Для каждого элемента массива shortest_path_root_list[i] найдите минимальный индекс элемента массива binary_search[k], ближайшего по
//  значению к shortest_path_root_list[i]. n ≤ 110000, m ≤ 1000. Время работы поиска для каждого элемента shortest_path_root_list[i]: O(log(k)).

#define MAX_COUNT_ARRAY_FIRST 110000
#define MAX_COUNT_ARRAY_SECOND 1000

typedef struct {
    size_t begin;
    size_t end;
} interval_t;

void exponential_search(const int key, const int *array, const size_t left, const size_t right, interval_t &intr) {
    size_t begin = left;
    size_t end = left + 1;

    while (end < right) {
        if (key > array[end]) {
            begin = end;

            end *= 2;
        } else {
            intr.begin = begin;
            intr.end = end;
            return;
        }
    }

    intr.begin = begin / 2;
    intr.end = right - 1;
}

size_t binary_search(const int key, const int* array, size_t left, size_t right) {
    if (key > array[right]) {
        return right;
    }

    if (key < array[left]) {
        return left;
    }

    while (left < right) {
        size_t mid = (left + right) / 2;

        if (key > array[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    //std::cout << left << " " << right << std::endl;
    //std::cout << array[left] << " " << array[right] << std::endl;

    if (array[right] - key >= key - array[right -1]) {
        return right - 1;
    } else {
        return right;
    }
}

int *input_array(size_t max_count, size_t &count) {
    std::cin >> count;

    assert(count <= max_count);

    int *res = new int [count];

    for (size_t i = 0; i < count; ++i) {
        std::cin >> res[i];
    }

    return res;
}

int main() {
    size_t length_a = 0;
    int *A = input_array(MAX_COUNT_ARRAY_FIRST, length_a);

    size_t length_b = 0;
    int *B = input_array(MAX_COUNT_ARRAY_SECOND, length_b);

    interval_t *intr = new interval_t;
    if (!intr) {
        return -1;
    }

    for (size_t i = 0; i < length_b; ++i) {
        exponential_search(B[i], A, 0, length_a, *intr);

        size_t res = binary_search(B[i], A, intr->begin, intr->end);

        std::cout << res << " ";
    }

    delete intr;

    delete[] A;

    delete[] B;


    return EXIT_SUCCESS;
}
