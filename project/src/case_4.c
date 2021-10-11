#include "case_4.h"
#include <stdio.h>

void Special_printf_of_num(int num) {
    int i;
    for (i = 2; i < num; ++i) {
        if (num % i == 0) {
            printf("%d\n", 0);
            break;
        }
    }
    printf("%d\n", 1);
}

