#include "case_4.h"
#include <stdio.h>

int rec_counter(int num, int pos) {
    printf("%d", pos);
    if (pos == num) {
       return 0;
    } else {
       if (num > 1) {
           printf(" ");
           rec_counter(num, ++pos);
       } else {
           printf(" ");
           rec_counter(num, --pos);
       }
    }
    return 0;
}
