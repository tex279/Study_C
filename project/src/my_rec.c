#include <my_rec.h>
#include <stdio.h>

#define IN_UP    1
#define IN_DOWN -1

void direct_rec_foo(int num, int pos) {
    int direct = IN_UP;
    if (num < pos) {direct = IN_DOWN;}
    rec(num, pos, direct);
}

int rec(int num, int pos, int direct) {
    if (pos == num) {
        printf("%d", pos);
        return 0;
    }
    printf("%d ", pos);
    rec(num, pos+direct, direct);
    return 0;
}
