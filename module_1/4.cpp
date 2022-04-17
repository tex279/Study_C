#include <iostream>

#define START_CAPACITY 16

template<typename T>
struct ProcessElement {
    T total_time;
    T worked_time;
    int priority;
};

template<typename T>
class Less {
public:
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template<typename T>
class More {
public:
    bool operator() (const T& l, const T& r) const {
        return l > r;
    }
};

template<typename T, class CompareRule = More<T>>
class Heap {
    size_t capacity;
    size_t size;

    T *array;

    CompareRule rule;

    void SiftUp(size_t pos);
    void SiftDown(size_t pos);

    void Resize();
public:
    bool IsEmpty();
    bool IsFull();

    void Add(T data);
    T ExtractTop();

    void Print(std::ostream &output);

    Heap();
    Heap(T *arr, size_t size_arr);
    ~Heap();

    Heap(const T& other) = delete;
    Heap &operator=(const Heap &other) = delete;
};

template<typename T, class CompareRule>
Heap<T, CompareRule>::Heap() {
    array = new T[START_CAPACITY];
    capacity = START_CAPACITY;
    size = 0;
}

template<typename T, class CompareRule>
Heap<T, CompareRule>::Heap(T *arr, size_t size_arr) : Heap() {
    while (capacity < size_arr) {
        Resize();
    }

    size = size_arr;

    for (size_t i = 0; i < size; ++i) {
        array[i] = arr[i];
    }

    for (size_t i = size; i > 0; --i) {
        SiftDown(i - 1);
    }
}

template<typename T, class CompareRule>
Heap<T, CompareRule>::~Heap() {
    delete[] array;
}

template<typename T, class CompareRule>
bool Heap<T, CompareRule>::IsEmpty() {
    return size == 0;
}

template<typename T, class CompareRule>
bool Heap<T, CompareRule>::IsFull() {
    return size == capacity;
}

template<typename T, class CompareRule>
void Heap<T, CompareRule>::Resize() {
    capacity *= 2;

    T *new_buf = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        new_buf[i] = array[i];
    }

    delete[] array;

    array = new_buf;
}

template<typename T, class CompareRule>
void Heap<T, CompareRule>::SiftUp(size_t pos) {
    size_t pos_parent = (pos - 1) / 2;
    while (rule(array[pos], array[pos_parent])) {

        std::swap(array[pos], array[pos_parent]);

        if (pos_parent == 0) {
            break;
        }

        pos = pos_parent;

        pos_parent = (pos - 1) / 2;
    }
}

template<typename T, class CompareRule>
void Heap<T, CompareRule>::SiftDown(size_t pos) {
    size_t child_left = 0;
    size_t child_right = 0;
    size_t max_child = 0;
    while (true) {
        child_left = 2 * pos + 1;
        child_right = 2 * pos + 2;

        if (child_left <= size - 1) {
            max_child = child_left;
        } else {
            break;
        }

        if (child_left < size - 1 && rule(array[child_right], array[max_child])) {
            max_child = child_right;
        }

        if (rule(array[pos], array[max_child])) {
            break;
        } else {
            std::swap(array[pos], array[max_child]);

            pos = max_child;
        }
    }

}

template<typename T, class CompareRule>
void Heap<T, CompareRule>::Add(T data) {
    if (IsEmpty()) {
        array[0] = data;
        ++size;
    } else {
        if (IsFull()) {
            Resize();
        }

        ++size;

        array[size - 1] = data;

        SiftUp(size - 1);
    }
}

template<typename T, class CompareRule>
T Heap<T, CompareRule>::ExtractTop() {
    T res = array[0];

    array[0] = array[size - 1];

    --size;

    SiftDown(0);

    return res;
}

template<typename T, class CompareRule>
void Heap<T, CompareRule>::Print(std::ostream &output) {
    for (size_t i = 0; i < size; ++i) {
        output << array[i] << "(" << i << ")" << " ";
    }

    output << std::endl;
}



void run_work(std::istream &input, std::ostream &output) {
    size_t count = 0;

    input >> count;

    int *array = new int [count];

    for (size_t i = 0; i < count; ++i) {
        input >> array[i];
    }

    Heap<int, More<int>> heap(array, count);

    heap.Print(output);
}

int main() {
    run_work(std::cin, std::cout);

    return EXIT_SUCCESS;
}
