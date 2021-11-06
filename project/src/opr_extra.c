#include <stdio.h>
#include <math.h>

#include <matrix.h>

int det(const Matrix* matrix, double* val) {
    if (check_ptr_matrix(matrix)) {
        return INCORRECT_INPUT;
    }

    if (matrix->m_rows != matrix->m_cols) {
        fprintf(stderr, "incorrect input, matrix must be square\n");
        return INCORRECT_INPUT;
    }

    Matrix* matrix_out = create_matrix(matrix->m_rows, matrix->m_cols);

    if (!matrix_out) {
        fprintf(stderr, "memory allocation error\n");
        return ERR_ALLOCATION;
    }

    for (size_t i = 0; i < matrix->m_rows; i++) {
        for (size_t j = 0; j < matrix->m_cols; j++) {
            matrix_out->m_data[i][j] = matrix->m_data[i][j];
        }
    }

    if (!step_viev(matrix_out)) {
        *val = 0;
        free_matrix(matrix_out);
        return SUCCESS;
    }

    *val = 1;

    for (size_t i = 0; i < matrix->m_rows; i++) {
        *val = *val * matrix_out->m_data[i][i];
    }

    free_matrix(matrix_out);
    return SUCCESS;
}

Matrix* adj(const Matrix* matrix) {
    if (check_ptr_matrix(matrix)) {
        return NULL;
    }

    if (matrix->m_rows == 1 && matrix->m_cols == 1) {
        Matrix* matrix_out = create_matrix(1, 1);
        matrix_out->m_data[0][0] = 1;
        return matrix_out;
    }

    Matrix* matrix_cur = create_matrix(matrix->m_rows, matrix->m_cols);

    if (!matrix_cur) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    for (size_t i = 0; i < matrix->m_rows; i++) {
        base_element val = 0;
        for (size_t j = 0; j < matrix->m_cols; j++) {
            Matrix* cur_munor = create_minor(matrix, i, j);
            det(cur_munor, &val);
            free_matrix(cur_munor);
            matrix_cur->m_data[i][j] = pow(-1, (i+j)) * val;
        }
    }

    Matrix* matrix_out = transp(matrix_cur);

    if (!matrix_out) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    free_matrix(matrix_cur);
    return  matrix_out;
}

Matrix* inv(const Matrix* matrix) {
    if (check_ptr_matrix(matrix)) {
        return NULL;
    }

    base_element val = 0;

    det(matrix, &val);

    Matrix* adt_to_matrix = adj(matrix);

    if (!adt_to_matrix) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    if (!val) {
        fprintf(stderr, "division by zero\n");
        return NULL;
    }

    Matrix* matrix_out = mul_scalar((adt_to_matrix), 1.0 / val);

    if (!matrix_out) {
        fprintf(stderr, "memory allocation error\n");
        free_matrix(adt_to_matrix);
        return NULL;
    }

    free_matrix(adt_to_matrix);
    return matrix_out;
}
