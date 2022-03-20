#include <stdio.h>

#include "my_rec.h"

void row_num(int num) {
    if (num == 1) {
        printf("%d", num);

        return;
    }

    if (num > 1) {
        row_num(num - 1);

        printf(" %d", num);
    } else {
        row_num(num + 1);

        printf(" %d", num);
    }
}
