#include <check_num.h>
#include <stdio.h>
#include <math.h>

int check_prime_num(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i < round(num/2)-1; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

