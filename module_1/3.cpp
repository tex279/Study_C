#include <stdio.h>
#include <iostream>
#include <cassert>

//  Реализовать дек с динамическим зацикленным буфером.

#define COUNT_COMMAND 1000000

#define START_CAPACITY 16

#define PUSH_FRONT 1
#define POP_FRONT 2
#define PUSH_BACK 3
#define POP_BACK 4

class Deque {
    size_t capacity;
    size_t size;

    size_t first;
    size_t last;

    int *array;

    void Resize();
public:
    bool IsEmpty();
    bool IsFull();

    void PushFront(int data);
    void PushBack(int data);

    int PopFront();
    int PopBack();

    void Print();

    Deque();
    virtual ~Deque();

    Deque(const Deque &other) = delete;
    Deque& operator=(const Deque &other) = delete;
};

Deque::Deque() {
    array = new int[START_CAPACITY];
    capacity = START_CAPACITY;
    size = 0;

    first = 0;
    last = 0;
}

Deque::~Deque() {
    delete[] array;
}

bool Deque::IsEmpty() {
    return size == 0;
}

bool Deque::IsFull() {
    return size == capacity;
}

void Deque::Resize() {
    int *new_buf = new int[capacity * 2];
    for (size_t i = 0; i < size; ++i) {
        new_buf[i] = array[i];
    }

    delete array;

    array = new_buf;
}

void Deque::PushFront(int data) {
    if (IsEmpty()) {
        array[first] = data;

        ++size;
    } else {
        if (IsFull()) {
            Resize();
        }

        first = (first + size - 1) % size;

        array[first] = data;

        ++size;
    }
}

void Deque::PushBack(int data) {
    std::cout << last << " " << size << " " << array[last] << std::endl;

    if (IsEmpty()) {
        array[last] = data;

        ++size;
    } else {
        if (IsFull()) {
            Resize();
        }

        last = (last + size + 1) % size;

        array[last] = data;

        ++size;
    }

    std::cout << last << " " << size << " " << array[last] << std::endl;
}

int Deque::PopFront() {
    if (IsEmpty()) {
        return -1;
    }

    int res = array[first];

    first = (first + size + 1) % size;

    --size;

    return res;
}

int Deque::PopBack() {
    if (IsEmpty()) {
        return -1;
    }

    int res = array[last];

    last = (last + size - 1) % size;

    --size;

    return res;
}

void Deque::Print() {
    //  std::cout << first << " " << size << std::endl;

   for (size_t i = 0 ; i < size; ++i) {
       std::cout << array[(i + first + size) % (size)] << " ";
   }

   std::cout << std::endl;
}

void run_work(std::istream &input, std::ostream &output) {
    Deque deque;

    size_t count_operation = 0;
    input >> count_operation;

    assert(count_operation <= COUNT_COMMAND);

    for (size_t i = 0; i < count_operation; i++) {
        size_t type_operation = 0;

        int value = 0;

        input >> type_operation >> value;
        switch (type_operation) {
            case PUSH_FRONT: {
                deque.PushFront(value);

                deque.Print();
                break;
            }
            case POP_FRONT: {
                int res_pop = deque.PopFront();

                if (res_pop != value) {
                    output << "NO" << std::endl;
                } else {
                    output << "YES" << std::endl;
                }

                deque.Print();
                break;
            }
            case PUSH_BACK: {
                deque.PushBack(value);

                deque.Print();
                break;
            }
            case POP_BACK: {
                int res_pop = deque.PopBack();

                if (res_pop != value) {
                    output << "NO" << std::endl;
                } else {
                    output << "YES" << std::endl;
                }

                deque.Print();
                break;
            }
            default: {
                break;
            }

        }
    }

}

int main() {
    run_work(std::cin, std::cout);

    return EXIT_SUCCESS;
}
