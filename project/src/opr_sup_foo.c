#include <stdio.h>

#include <matrix.h>

Matrix* create_minor(const Matrix* matrix, const size_t row, const size_t col) {
    Matrix* minor = create_matrix(matrix->m_rows-1, matrix->m_cols-1);

    size_t min_row = 0;
    for (size_t i = 0; i < matrix->m_rows; i++) {
        if (i == row) {
            continue;
        }

        size_t min_col = 0;
        for (size_t j = 0; j < matrix->m_cols; j++) {
            if (j != col) {
                minor->m_data[min_row][min_col] = matrix->m_data[i][j];
                min_col++;
            }
        }
        min_row++;
    }
    return minor;
}

int step_viev(Matrix* matrix) {
    for (size_t k = 0; k < matrix->m_rows; k++) {
        if (check_null_row(matrix, k) || check_null_col(matrix, k)) {
            return false;
        }

        for (size_t i = 1 + k; i < matrix->m_rows; i++) {
            check_null_diag_el(matrix, k);

            base_element_t mull = matrix->m_data[i][k] / matrix->m_data[k][k];

            for (size_t j = 0; j < matrix->m_rows; j++) {
                matrix->m_data[i][j] = matrix->m_data[i][j] - mull * matrix->m_data[k][j];
            }
        }
    }
    return true;
}
