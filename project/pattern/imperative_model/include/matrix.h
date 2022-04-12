#pragma once //  NOLINT

#define ERR_ALOC_M "memory allocation error\n"

size_t **create_matrix(const size_t row, const size_t col);

void free_matrix(size_t **matrix, const size_t row);
