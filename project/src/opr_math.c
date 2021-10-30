#include <stdio.h>

#include <matrix.h>

Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (check_ptr_matrix(matrix)) {
        return NULL;
    }

    Matrix *matrix_out = create_matrix(matrix->m_rows, matrix->m_cols);

    for (size_t i = 0; i < matrix->m_rows; i++) {
        for (size_t j = 0; j < matrix->m_cols; j++) {
            matrix_out->m_data[i][j] = val*matrix->m_data[i][j];
        }
    }
    return matrix_out;
}

Matrix* transp(const Matrix* matrix) {
    if (check_ptr_matrix(matrix)) {
        return NULL;
    }

    Matrix *matrix_out = create_matrix(matrix->m_cols, matrix->m_rows);

    for (size_t i = 0; i < matrix->m_cols; i++) {
        for (size_t j = 0; j < matrix->m_rows; j++) {
            matrix_out->m_data[i][j] = matrix->m_data[j][i];
        }
    }
    return matrix_out;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (check_ptr_matrix(l)) {
        return NULL;
    }

    if (check_ptr_matrix(r)) {
        return NULL;
    }

    Matrix *matrix_out = create_matrix(r->m_rows, r->m_cols);

    for (size_t i = 0; i < matrix_out->m_rows; i++) {
        for (size_t j = 0; j < matrix_out->m_cols; j++) {
            matrix_out->m_data[i][j] = l->m_data[i][j] + r->m_data[i][j];
        }
    }
    return matrix_out;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if (check_ptr_matrix(l)) {
        return NULL;
    }

    if (check_ptr_matrix(r)) {
        return NULL;
    }

    Matrix *matrix_out = create_matrix(l->m_rows, l->m_cols);

    for (size_t i = 0; i < matrix_out->m_rows; i++) {
        for (size_t j = 0; j < matrix_out->m_cols; j++) {
            matrix_out->m_data[i][j] = l->m_data[i][j] - r->m_data[i][j];
        }
    }
    return matrix_out;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (check_ptr_matrix(l)) {
        return NULL;
    }

    if (check_ptr_matrix(r)) {
        return NULL;
    }

    if (l->m_cols != r->m_rows) {
        fprintf(stdout, "these matrices cannot be multiplied\n");
        return NULL;
    }

    Matrix *matrix_out = create_matrix(l->m_rows, r->m_cols);

    size_t num_iter = l->m_cols;

    for (size_t i = 0; i < matrix_out->m_rows; i++) {
        for (size_t j = 0; j < matrix_out->m_cols; j++) {
            for (size_t pos = 0; pos < num_iter; pos++) {
                matrix_out->m_data[i][j] += l->m_data[i][pos] * r->m_data[pos][j];
            }
        }
    }
    return matrix_out;
}
