#include <stdio.h>

#include <matrix.h>

int check_null_row(const Matrix* matrix, const size_t row) {
    size_t pos = 0;

    while (matrix->m_data[row][pos] == 0) {
        if (pos == matrix->m_rows - 1) {
            return TRUE;
        }
        pos++;
    }
    return FALSE;
}

int check_null_col(const Matrix* matrix, const size_t col) {
    size_t pos = 0;

    while (matrix->m_data[pos][col] == 0) {
        if (pos == matrix->m_cols - 1) {
            return TRUE;
        }
        pos++;
    }
    return FALSE;
}

int check_null_diag_el(Matrix* matrix, const size_t pos) {
    if (matrix->m_data[pos][pos] == 0) {
        size_t not_zero_col = 1;

        while (matrix->m_data[pos][pos + not_zero_col] == 0) {
            not_zero_col++;
        }

        plus_col(matrix, pos, pos + not_zero_col);
        return TRUE;
    }
    return FALSE;
}

int plus_col(Matrix* matrix, const size_t target, const size_t sourse) {
    for (size_t i = 0; i < matrix->m_rows; i++) {
        matrix->m_data[i][target] = matrix->m_data[i][target] + matrix->m_data[i][sourse];
    }
    return SUCCESS;
}
