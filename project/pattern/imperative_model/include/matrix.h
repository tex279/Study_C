#pragma once //  NOLINT

#include "load_database.h"

size_t **create_matrix(const size_t row, const size_t col);

void free_matrix(size_t **matrix, const size_t row);
