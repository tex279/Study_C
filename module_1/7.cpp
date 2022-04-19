#include <iostream>
#include <cassert>

//    Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6.
//    Отсортировать массив методом MSD по битам (бинарный QuickSort).


#define MAX_COUNT_ARRAY_FIRST 110000
#define MAX_COUNT_ARRAY_SECOND 1000


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
    size_t length = 0;
    int *array = input_array(MAX_COUNT_ARRAY_FIRST, array);

    delete[] array;

    return EXIT_SUCCESS;
}
