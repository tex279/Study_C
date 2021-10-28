#include <stdio.h>

#include <matrix.h>

#define PATH_CRE "/home/andeo/GitHub/TechPark-2021/project/tests/data/test_matrix_creating/case_3/in.txt"
#define PATH_INV "/home/andeo/GitHub/TechPark-2021/project/tests/data/test_matrix_inverse/case_1/in.txt"
#define PATH_DET "/home/andeo/GitHub/TechPark-2021/project/tests/data/test_matrix_determinant/case_0/in.txt"
#define PATH_ADJ_IN "/home/andeo/GitHub/TechPark-2021/project/tests/data/test_matrix_adjugate/case_1/in.txt"
#define PATH_ADJ_OUT "/home/andeo/GitHub/TechPark-2021/project/tests/data/test_matrix_adjugate/case_1/out.txt"

#define TEST_MATRIX_CREATING  1
#define TEST_GET_ROWS_COLS    2
#define TEST_DET              3
#define TEST_ADJ              5
#define TEST_INV              6

int main(void) {
    int choice = 0;
    fprintf(stdout, "%s%s%s%s%s%s",
            "please enter action\n",
            "1 - creating mat from file\n",
            "2 - get rows, get cols\n",
            "3 - det\n",
            "5 - adj\n",
            "6 - inv_mat\n");
    while (fscanf(stdin, "%d", &choice) != -1) {
        switch (choice) {
            case TEST_MATRIX_CREATING: {
                Matrix mat;
                mat = *(create_matrix_from_file(PATH_CRE));
                print_matrix_my(&mat);
                free_matrix(&mat);
                break;
            }
            case TEST_GET_ROWS_COLS: {
                Matrix mat;
                mat = *(create_matrix_from_file(PATH_CRE));
                size_t i = 0;
                size_t ii = 0;
                get_cols(&mat, &i);
                get_rows(&mat, &ii);
                fprintf(stdout, "%zu %zu\n", i, ii);
                free_matrix(&mat);
                break;
            }
            case TEST_DET: {
                Matrix mat;
                mat = *(create_matrix_from_file(PATH_DET));
                print_matrix_my(&mat);
                double val;
                det(&mat, &val);
                fprintf(stdout, "%f\n", val);
                free_matrix(&mat);
                break;
            }
            case TEST_ADJ : {
                Matrix mat_in, mat_out;
                mat_in = *(create_matrix_from_file(PATH_ADJ_IN));
                mat_out = *(create_matrix_from_file(PATH_ADJ_OUT));
                mat_in = *(adj(&mat_in));
                print_matrix_my(&mat_in);
                print_matrix_my(&mat_out);
                free_matrix(&mat_out);
                free_matrix(&mat_in);
                break;
            }
            case TEST_INV: {
                Matrix mat, inv_mat;
                mat = *(create_matrix_from_file(PATH_INV));
                print_matrix_my(&mat);
                inv_mat = *(inv(&mat));
                print_matrix_my(&inv_mat);
                free_matrix(&mat);
                free_matrix(&inv_mat);
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
