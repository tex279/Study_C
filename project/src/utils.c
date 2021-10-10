#include "utils.h"

size_t timer_from(char from) {
    size_t counter;
    for (char i = from; i >= 0; --i) {
        ++counter;
        printf(i);
    }
    return counter;
}

// TODO: Implement `power of` function

int custom_pow(int base, int power) {
    return (base^power);
}

