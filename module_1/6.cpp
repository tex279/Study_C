#include <algorithm>
#include <iostream>
#include <cassert>

//    Реализуйте стратегию выбора опорного элемента “медиана трёх”.
//    Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.


//    Дано множество целых чисел из [0..10^online_generator_txt.txt] размера n.
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
    int rand_pos_1 = (rand() % (right - left - 1)) + left;
    int rand_pos_2 = (rand() % (right - left - 1)) + left;
    int rand_pos_3 = (rand() % (right - left - 1)) + left;

    T mediana = (array[rand_pos_1] + array[rand_pos_2] + array[rand_pos_3]) / 3.0;

    if (rule(std::abs(mediana - array[rand_pos_2]), std::abs(mediana - array[rand_pos_1])))
        std::swap(rand_pos_2, rand_pos_1);
    if (rule(std::abs(mediana - array[rand_pos_3]), std::abs(mediana - array[rand_pos_2])))
        std::swap(rand_pos_3, rand_pos_2);
    if (rule(std::abs(mediana - array[rand_pos_2]), std::abs(mediana - array[rand_pos_1])))
        std::swap(rand_pos_2, rand_pos_1);

    return rand_pos_1;
}

template<typename T, class CompareRule = Less<T>>
int partition(T *array, int left, int right, CompareRule rule = Less<T>()) {
    if (right - left <= 1) {
        return left;
    }

    int pivot = get_median(array, left, right, rule);

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
T find_k_statistics(T *array, int right, int target, CompareRule rule = Less<T>()) {
    srand(time(NULL));

    int left = 0;
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

    std::cout << find_k_statistics(array, length, (length * 0.1)) << std::endl;
    std::cout << find_k_statistics(array, length, (length * 0.5)) << std::endl;
    std::cout << find_k_statistics(array, length, (length * 0.9)) << std::endl;

    delete[] array;

    return EXIT_SUCCESS;
}
