#include <my_rec.h>
#include <stdio.h>



void direct(int num, int pos) {
    if (num > pos)
        rec_up(num, pos);
    else
        rec_down(num, pos);
}


int rec_up(int num, int pos) {
    if (pos == num) {
        printf("%d", pos);
        return 0;
    } else {
        printf("%d ", pos);
        rec_up(num, ++pos);
    }
    return 0;
}

int rec_down(int num, int pos) {
    if (pos == num) {
        printf("%d", pos);
        return 0;
    } else {
        printf("%d ", pos);
        rec_down(num, --pos);
    }
    return 0;
}

