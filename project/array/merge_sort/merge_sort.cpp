#include <iostream>
#include <cassert>

//    На числовой прямой окрасили N отрезков.
//    Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
//    N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].

#define MAX_COUNT_LINES 10000
#define MAX_LENGTH 10e9

struct Point {
    size_t coordinate;
    int thickness;

    friend std::ostream& operator<<(std::ostream &os, const Point &it)  {
        return os << it.coordinate << " " << it.thickness << std::endl;
    }
};

class SortRulePoints {
public:
    bool operator()(const Point &l, const Point &r) const {
        return l.coordinate < r.coordinate;
    }
};

Point *input_array(size_t max_count, size_t &count) {
    std::cin >> count;

    assert(count <= max_count);

    Point *res = new Point [count * 2];

    for (size_t i = 0; i < count; ++i) {
        std::cin >> res[2 * i].coordinate >> res[2 * i + 1].coordinate;

        assert(res[2 * i].coordinate <= MAX_LENGTH);
        assert(res[2 * i + 1].coordinate <= MAX_LENGTH);


        res[2 * i].thickness = 1;

        res[2 * i + 1].thickness = -1;
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

template<typename T>
class More {
public:
    bool operator()(const T &l, const T &r) const {
        return l > r;
    }
};

template<typename T, class CompareRule = Less<T>>
void merge_base(T *array, size_t low, size_t mid, size_t high, T *tmp, CompareRule rule = Less<T>()) {
    size_t i;
    size_t j;
    for (i = mid + 1; i > low; i--) {
        tmp[i - 1] = array[i - 1];
    }

    for (j = mid; j < high; j++) {
        tmp[high + mid - j] = array[j + 1];
    }

    for (size_t k = low; k <= high; k++) {
        if (rule(tmp[j], tmp[i])) {
            array[k] = tmp[j--];
        } else {
            array[k] = tmp[i++];
        }
    }
}

template<typename T, class CompareRule = Less<T>>
void merge_sort(T *array, size_t low, size_t high, T *tmp, CompareRule rule = Less<T>()) {
    size_t mid = (low + high) / 2;

    if (low == mid && high == mid) {
        return;
    }

    merge_sort(array, low, mid, tmp, rule);

    merge_sort(array, mid + 1, high, tmp, rule);

    merge_base(array, low, mid, high, tmp, rule);
}

template<typename T, class CompareRule = Less<T>>
void merge(T *array, size_t length, CompareRule rule = Less<T>()) {
    T *tmp = new T [length];

    merge_sort(array, 0, length - 1, tmp, rule);

    delete [] tmp;
}

int get_res(const Point *array, const size_t count_points) {
    int total_length = 0;
    int cur_thickness = 0;
    for (size_t i = 0; i < count_points; ++i) {
        cur_thickness += array[i].thickness;

        if (cur_thickness > 0) {
            total_length += array[i + 1].coordinate - array[i].coordinate;
        }
    }

    return total_length;
}

int main() {
    size_t count_lines = 0;
    Point *array = input_array(MAX_COUNT_LINES, count_lines);

    size_t count_points = 2 * count_lines;

    SortRulePoints rule;

    merge(array,count_points, rule);

    std::cout << get_res(array, count_points) << std::endl;

    delete[] array;

    return EXIT_SUCCESS;
}
