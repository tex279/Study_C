#include <stdio.h>

#include <matrix.h>

int check_index(const int rows , const int cols) {
    if (rows < 1 || cols < 1) {
        fprintf(stderr, "incorrect input, matrix must have at least 1 element\n");
        return true;
    }

    return false;
}

int check_ptr_matrix(const Matrix* matrix) {
    if (!matrix) {
        fprintf(stderr, "incorrect input, there should be a ptr on the matrix\n");
        return true;
    }

    if (check_index(matrix->m_rows, matrix->m_cols)) {
        return true;
    }

    return false;
}
