#include <stdio.h>

#include <matrix.h>

int get_rows(const Matrix* matrix, size_t* rows) {
    if (check_ptr_matrix(matrix)) {
        return INCORRECT_INPUT;
    }

    *rows = matrix->m_rows;
    return SUCCESS;
}
int get_cols(const Matrix* matrix, size_t* cols) {
    if (check_ptr_matrix(matrix)) {
        return INCORRECT_INPUT;
    }

    *cols = matrix->m_cols;
    return SUCCESS;
}
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (check_ptr_matrix(matrix)) {
        return INCORRECT_INPUT;
    }

    if (row > matrix->m_rows || col > matrix->m_cols) {
        fprintf(stderr, "incorrect input, the requested element is out of the dimension of the matrix\n");
        return INCORRECT_INPUT;
    }

    *val = matrix->m_data[row][col];
    return SUCCESS;
}
int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (check_ptr_matrix(matrix)) {
        return INCORRECT_INPUT;
    }

    if (row > matrix->m_rows || col > matrix->m_cols) {
        fprintf(stderr, "incorrect input, the requested element is out of the dimension of the matrix\n");
        return INCORRECT_INPUT;
    }

    matrix->m_data[row][col] = val;
    return SUCCESS;
}
