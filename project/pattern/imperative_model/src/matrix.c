#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

size_t **create_matrix(const size_t row, const size_t col) {
    size_t **matrix  = calloc(row, sizeof(size_t*));
    if (!matrix) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    for (size_t i = 0; i < row; ++i) {
        matrix[i] = calloc(col, sizeof(size_t));
        if (!matrix[i]) {
            fprintf(stderr, "memory allocation error\n");
            return NULL;
        }
    }

    return matrix;
}

void print_matrix(size_t **matrix, const size_t row, const size_t col) {
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            fprintf(stdout, "%zu ", matrix[i][j]);
        }

        fprintf(stdout, "\n");
    }
}

void free_matrix(size_t **matrix, const size_t row) {
    for (size_t i = 0; i < row - 1; ++i) {
        free(matrix[i]);
    }

    free(matrix);
}
