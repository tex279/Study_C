#include "check_num.h"

#define TRUE    1
#define FALSE   0

int check_prime_num(int num) {
    if (num <= 1) {
        return FALSE;
    }

    for (int i = 2; i * i < num; i++) {
        if (num % i == 0) {
            return FALSE;
        }
    }

    return TRUE;
}

