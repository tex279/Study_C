#include <iostream>
#include <cassert>

//    Реализуйте стратегию выбора опорного элемента “медиана трёх”.
//    Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.


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

template<typename T>
class Less {
public:
    bool operator()(const T &l, const T &r) const {
        return l < r;
    }
};

template<typename T, class CompareRule = Less<T>>
int get_median(T *array, int left, int right, CompareRule rule = Less<T>()) {
    int median = (left + right) / 2;

    if (rule(array[left], array[right])) {
        std::swap(left, right);
    }

    if (rule(array[left], array[median])) {
        std::swap(left, median);
    }

    if (rule(array[median], array[right])) {
        std::swap(median, right);
    }

    return median;
}

template<typename T, class CompareRule = Less<T>>
int partition(T *array, int left, int right, CompareRule rule = Less<T>()) {
    if (right - left <= 1) {
        return left;
    }

    int pivot = get_median(array, left, right - 1, rule);

    std::swap(array[right - 1], array[pivot]);

    T value_pivot = array[right - 1];

    int i = right - 1;
    int j = right - 2;

    while (j >= left) {
        if (rule(value_pivot, array[j])) {
            --i;

            std::swap(array[i], array[j]);
        }
        --j;
    }

    std::swap(array[i], array[right - 1]);

    return i;
}

template<typename T, class CompareRule = Less<T>>
T find_k_statistics(T *array, int left, int right, int target, CompareRule rule = Less<T>()) {
    while (true) {
        int pos_pivot = partition(array, left, right, rule);
        if (pos_pivot == target) {
            break;
        }

        if (target < pos_pivot) {
            right = pos_pivot;
        } else {
            left = pos_pivot + 1;
        }
    }

    return array[target];
}


int main() {
    size_t length = 0;
    int *array = input_array(MAX, length);

    std::cout << find_k_statistics(array, 0, length, (length * 0.1)) << std::endl;
    std::cout << find_k_statistics(array, 0, length, (length * 0.5)) << std::endl;
    std::cout << find_k_statistics(array, 0, length, (length * 0.9)) << std::endl;

    delete[] array;

    return EXIT_SUCCESS;
}