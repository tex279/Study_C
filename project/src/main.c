#include <stdio.h>

#include <matrix.h>

#define PATH "/home/andeo/GitHub/TechPark-2021/project/tests/data/test_matrix_creating/case_3/in.txt"

#define TEST_MATRIX_CREATING  1
#define TEST_GET_ROWS_COLS    2

int main(void) {
    int choice = 0;
    fprintf(stdout, "%s%s%s",
            "please enter action\n",
            "1 - creating mat from file\n",
            "2 - get rows, get cols\n");
    while (fscanf(stdin, "%d", &choice) != -1) {
        switch (choice) {
            case TEST_MATRIX_CREATING: {
                Matrix mat;
                mat = *(create_matrix_from_file(PATH));
                print_matrix_my(&mat);
                break;
            }
            case TEST_GET_ROWS_COLS : {
                Matrix mat;
                mat = *(create_matrix_from_file(PATH));
                size_t i = 0;
                size_t ii = 0;
                get_cols(&mat, &i);
                get_rows(&mat, &ii);
                fprintf(stdout, "%zu %zu\n", i, ii);
                break;
            }
            default: {
                fprintf(stdout, "%s\n", "error");
                break;
            }
        }
        return 0;
    }
}
