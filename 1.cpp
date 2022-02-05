#include <stdio.h>
#include <iostream>

#define SUCCESS 1
#define LENGTH 3

void change_array(int array[], size_t up_index, size_t static_index) {
    array[up_index] -= array[static_index];
}

void r_change_array(int array[], size_t up_index, size_t static_index) {
    array[up_index] += array[static_index];
}

void print_arr(int array[]) {
    for (size_t i = 0; i < LENGTH; i++) {
        if (i == LENGTH - 1) {
            std::cout << array[i] << std::endl;
            return;
        }

        std::cout << array[i] << " ";
    }
}

void print_response(bool array[]) {
    for (size_t i = 0; i < LENGTH; i++) {
        if (array[i] == true) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
}

void sort(int array[]) {
    for (size_t j = 0; j < LENGTH - 1; j++) {
        for (size_t i = 0; i < LENGTH - j - 1; i++) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
            }
        }
    }
}

int* copy_array(int array[]) {
    int* a = new int[LENGTH];

    for (size_t i = 0; i < LENGTH; i++) {
        a[i] = array[i];
    }

    return a;
}

void check_combinations(int array[]) {
    bool response[LENGTH];

    int *sorted = copy_array(array);
    sort(sorted);

    for (size_t k = 0; k < LENGTH; k++) {
        if (array[k] == sorted[1]) {
            response[k] = true;
        }
    }

    delete[] sorted;

    for (size_t i = 0; i < LENGTH; i++) {
        for (size_t j = 0; j < LENGTH; j++) {
            if (i != j) {
                change_array(array, i, j);
                //std::cout << "ИЗМЕНИЛ BASE " << i + 1 << " НА " << j + 1 << std::endl;
                //print_arr(array);

                int *sorted = copy_array(array);
                sort(sorted);
                //std::cout << "ОТСОРТИРОВАЛ BASE " << i + 1 << " ПРИ " << j + 1 << std::endl;
                //print_arr(sorted);

                for (size_t k = 0; k < LENGTH; k++) {
                    if (array[k] == sorted[1]) {
                        response[k] = true;
                    }
                }

                r_change_array(array, i, j);
                delete[] sorted;
            }
        }
    }

    print_response(response);
}

int main() {
    int array[LENGTH];

    int data;

    for (size_t i = 0; i < LENGTH; i++) {
        std::cin >> data;

        array[i] = data;
    }

    check_combinations(array);

    return SUCCESS;
}
