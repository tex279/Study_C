#include <stdio.h>
#include <iostream>

#define MAX_ANAGRAM 10000

#define START_CAPACITY 16

class Stack {
    size_t capacity;
    size_t size;

    size_t first;
    size_t last;

    char *array;

    void Resize();
public:
    bool IsEmpty();
    bool IsFull();

    void PushBack(char data);

    char PopBack();

    char GetBack();

    void Print();

    Stack();
    ~Stack() = default;
};

Stack::Stack() {
    array = new char[START_CAPACITY];
    capacity = START_CAPACITY;
    size = 0;

    last = 0;
}

bool Stack::IsEmpty() {
    return size == 0;
}

bool Stack::IsFull() {
    return size == capacity;
}

void Stack::Resize() {
    capacity *= 2;

    char *new_buf = new char[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        new_buf[i] = array[i];
    }

    delete array;

    array = new_buf;
}

void Stack::PushBack(char data) {
    if (IsEmpty()) {
        array[last] = data;
    } else {
        if (IsFull()) {
            Resize();
        }

        ++last;

        array[last] = data;

    }

    ++size;
}

char Stack::PopBack() {
    if (IsEmpty()) {
        return -1;
    }

    --size;

    int res = array[last];

    array[last] = {};

    --last;

    return res;
}

void Stack::Print() {
    for (size_t i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

char Stack::GetBack() {
    return array[last];
}

bool check_anagram(std::string &word_base, std::string &word_sample) {
    Stack stack;

    size_t length_1 = word_base.length();

    bool result = true;

    size_t i = 0;
    size_t j = 0;
    while (j < length_1) {
        if (i < length_1) {
            stack.PushBack(word_base[i]);
        }

        if (stack.GetBack() == word_sample[j]) {
            stack.PopBack();

            ++j;
        } else if (i >= length_1) {
            result = false;

            break;
        }

        ++i;
    }

    return result;
}

void run_work() {
    std::string word_base;
    std::string word_sample;

    std::cin >> word_base >> word_sample;


    if (check_anagram(word_base, word_sample)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}

int main() {
    run_work();

    return EXIT_SUCCESS;
}
