#include <stdio.h>
#include <stdlib.h>

#include <matrix.h>

Matrix* create_matrix(size_t rows, size_t cols) {
    if (check_index(rows, cols)) {
        return NULL;
    }

    Matrix *matrix_out = (Matrix*)calloc(1, sizeof(Matrix));

    if (!matrix_out) {
        fprintf(stdout, "memory allocation error\n");
        return NULL;
    }

    matrix_out->m_data = calloc(rows, sizeof(base_element*));

    if (!matrix_out->m_data) {
        free(matrix_out);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix_out->m_data[i] = calloc(cols, sizeof(base_element));

        if (!matrix_out->m_data[i]) {
            fprintf(stdout, "memory allocation error\n");
            for (size_t j = 0; j < i; j++) {
                free(matrix_out->m_data[i]);
            }

            free(matrix_out->m_data);
            free(matrix_out);
            return NULL;
        }
    }

    matrix_out->m_rows = rows;
    matrix_out->m_cols = cols;
    return matrix_out;
}

void free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->m_rows; i++) {
        free(matrix->m_data[i]);
    }

    free(matrix->m_data);
    free(matrix);
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* source = fopen(path_file, "r");

    if (!source) {
        fprintf(stdout, "impossible open file in your path\n");
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;

    if (fscanf(source, "%zu %zu", &rows, &cols) != 2) {
        fclose(source);
        fprintf(stdout, "incorrect input, there should be 2 values type - double\n");
        return NULL;
    }

    if (check_index(rows , cols)) {
        fclose(source);
        return NULL;
    }

    Matrix *matrix_out = create_matrix(rows, cols);

    if (!matrix_out) {
        fprintf(stdout, "memory allocation error\n");
        fclose(source);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (fscanf(source, "%lf", &(matrix_out->m_data[i][j])) != 1) {
                fclose(source);
                free_matrix(matrix_out);
                fprintf(stdout, "incorrect input, there should be 1 values type - double\n");
                return NULL;
            }
        }
    }

    fclose(source);
    return matrix_out;
}
