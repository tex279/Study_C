#include "utils.h"
#include <stddef.h>
#include <stdio.h>


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

// TODO(Alexandr_Anofrikov): Implement `power of` function

int custom_pow(int base, int power) {
    int result = 1;
    for (int i = 1; i <= power; ++i)
        result = result*base;
    return (result);
}

