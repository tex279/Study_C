#include <stdio.h>

#include <matrix.h>

int check_index(const int rows , const int cols) {
    if (rows < 1 && cols < 1) {
        fprintf(stdout, "incorrect input, matrix must have at least 1 element\n");
        return TRUE;
    }

    return FALSE;
}

int check_ptr_matrix(const Matrix* matrix) {
    if (!matrix) {
        fprintf(stdout, "incorrect input, there should be a ptr on the matrix\n");
        return TRUE;
    }

    if (check_index(matrix->m_rows, matrix->m_cols)) {
        return TRUE;
    }

    return FALSE;
}
