#include <stdio.h>

#include <matrix.h>

#define PATH "/project/tests/data/test_matrix_creating/case_0/in.txt"

int main(void) {
    create_matrix_from_file(PATH);
    return 0;
}
