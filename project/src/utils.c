#include <stddef.h>
#include <stdio.h>

#define INCORRECT_INPUT -1;

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        printf("%d", i);
        if (i > 0)
            printf(" ");
    }
    if (from > 0)
        printf("\n");
    return counter;
}

int custom_pow(int base, int power) {
    int result = 1;
    if (power < 0) {
        fprintf(stdout, "%s\n", "incorrect input");
        return INCORRECT_INPUT;
    }
    for (int i = 1; i <= power; ++i)
        result = result*base;
    return result;
}

