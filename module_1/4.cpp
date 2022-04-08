#include <stdio.h>
#include <iostream>
#include <cassert>

#define COUNT_COMMAND 1000000

#define START_CAPACITY 16

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
    ~Deque();
};


int main() {
    run_work(std::cin, std::cout);

    return EXIT_SUCCESS;
}
