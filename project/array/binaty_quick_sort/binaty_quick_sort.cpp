#include <iostream>
#include <cassert>

//    Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6.
//    Отсортировать массив методом MSD по битам (бинарный QuickSort).

#define MAX_COUNT_ARRAY 1000000

bool get_bit(u_int64_t number, size_t bit) {
    return ((number >> bit) & 1);
}


u_int64_t *input_array(size_t max_count, size_t &count) {
    std::cin >> count;

    assert(count <= max_count);

    u_int64_t *res = new u_int64_t [count];

    for (size_t i = 0; i < count; ++i) {
        std::cin >> res[i];
    }

    return res;
}


void binary_MSD(u_int64_t *arr, size_t begin, size_t end, size_t k = 63) {
    assert(arr != nullptr);

    size_t i = begin;
    size_t j = end;
    while (true) {
        while (!get_bit(arr[i], k) && i < end) {
            ++i;
        }

        while (get_bit(arr[j], k) && j > begin) {
            --j;
        }

        if (i < j) {
            std::swap(arr[i], arr[j]);
        } else {
            break;
        }
    }

    if (!k) {
        return;
    }

    //  По итогу работы вернехнего цикла i = j + structs.txt поэтому такой порядок для i и j для рекурсивного вызова.
    if (j - begin > 0) {
        binary_MSD(arr, begin, j, k - 1);
    }

    if (end - i > 0) {
        binary_MSD(arr, i, end, k - 1);
    }
}


int main() {
    size_t length = 0;
    u_int64_t *array = input_array(MAX_COUNT_ARRAY, length);

    binary_MSD(array, 0, length - 1);

    for(size_t i = 0; i < length; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    delete[] array;

    return EXIT_SUCCESS;
}
