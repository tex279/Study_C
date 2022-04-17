#include <stdio.h>
#include <iostream>
#include <cassert>

//    Дано множество целых чисел из [0..10^9] размера n.
//
//    Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
//      10% перцентиль
//      медиана
//      90% перцентиль
//    Требования:
//      К дополнительной памяти: O(n).
//      Среднее время работы: O(n)
//      Должна быть отдельно выделенная функция partition.
//      Рекурсия запрещена.
//      Решение должно поддерживать передачу функции сравнения снаружи.

#define MAX 10e9

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
    int *array = input_array(MAX, length);


    delete[] array;

    return EXIT_SUCCESS;
}
