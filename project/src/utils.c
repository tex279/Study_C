#include <stdio.h>

#include "utils.h"

#define INCORRECT_INPUT -1;

size_t timer_from(int from) {
    size_t counter = 0;

    for (int i = from; i >= 1; --i) {
        ++counter;

        printf("%d ", i);
    }

    if (from > 0) {
        ++counter;
        printf("0\n");
    }

    return counter;
}

int custom_pow(int base, int power) {
    if (power < 0) {
        fprintf(stdout, "%s\n", "incorrect input");
        return INCORRECT_INPUT;
    }

    int result = 1;

    for (int i = 0; i < power; ++i) {
        result = result * base;
    }

    return result;
}

