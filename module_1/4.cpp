#include <iostream>

#define START_CAPACITY 16

class Heap {
    size_t capacity;
    size_t size;

    size_t last;

    int *array;

    void SiftUp(size_t pos);
    void SiftDown(size_t pos);

    void Resize();
public:
    bool IsEmpty();
    bool IsFull();

    void Add(int data);
    int ExtractTop();

    void Print(std::ostream &output);

    Heap();
    Heap(int *arr, size_t size_arr);
    ~Heap();
};

Heap::Heap() {
    array = new int[START_CAPACITY];
    capacity = START_CAPACITY;
    last = 0;
    size = 0;
}

Heap::Heap(int *arr, size_t size_arr) : Heap() {
    while (capacity < size_arr) {
        Resize();
    }

    last = size_arr - 1;

    size = size_arr;

    for (size_t i = 0; i < size; ++i) {
        array[i] = arr[i];
    }

    for (size_t i = size; i > 0; --i) {
        SiftDown(i - 1);
    }
}

Heap::~Heap() {
    delete array;
}

bool Heap::IsEmpty() {
    return size == 0;
}

bool Heap::IsFull() {
    return size == capacity;
}

void Heap::Resize() {
    capacity *= 2;

    int *new_buf = new int[capacity];
    for (size_t i = 0; i < size; ++i) {
        new_buf[i] = array[i];
    }

    delete[] array;

    array = new_buf;
}

void Heap::SiftUp(size_t pos) {
    size_t pos_parent = (pos - 1) / 2;
    while (array[pos_parent] < array[pos]) {

        std::swap(array[pos_parent], array[pos]);

        if (pos_parent == 0) {
            break;
        }

        pos = pos_parent;

        pos_parent = (pos - 1) / 2;
    }
}

void Heap::SiftDown(size_t pos) {
    size_t child_left = 0;
    size_t child_right = 0;
    size_t max_child = 0;
    while (true) {
        child_left = 2 * pos + 1;
        child_right = 2 * pos + 2;

        if (child_left > last) {
            break;
        }

        if (array[child_left] > array[child_right]) {
            max_child = child_left;
        } else {
            max_child = child_right;
        }

        if (array[pos] > array[max_child]) {
            break;
        }

        std::swap(array[pos], array[max_child]);

        pos = max_child;
    }

}

void Heap::Add(int data) {
    if (IsEmpty()) {
        array[last] = data;
        size++;
    } else {
        if (IsFull()) {
            Resize();
        }

        last++;

        array[last] = data;

        size++;

        SiftUp(last);
    }
}

int Heap::ExtractTop() {
    int res = array[0];

    array[0] = array[last];

    size--;
    last--;

    SiftDown(0);

    return res;
}

void Heap::Print(std::ostream &output) {
    for (size_t i = 0; i < size; ++i) {
        output << array[i] << "(" << i << ")" << " ";
    }
    output << std::endl;
}

void run_work_place(std::istream &input, std::ostream &output) {
    size_t count = 0;

    input >> count;

    int *array = new int [count];

    for (size_t i = 0; i < count; ++i) {
        input >> array[i];
    }

    Heap heap(array, count);

    heap.Print(output);
}

void run_work(std::istream &input, std::ostream &output) {
    Heap heap;

    size_t count = 0;

    input >> count;

    int buf = 0;

    for (size_t i = 0; i < count; ++i) {
        input >> buf;
        heap.Add(buf);
    }

    heap.Print(output);
}

int main() {
    run_work_place(std::cin, std::cout);

    return EXIT_SUCCESS;
}
