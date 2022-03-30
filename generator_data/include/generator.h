#pragma once  //  NOLINT

#include <stddef.h>

#include "utils.h"

//  rand
char *get_rand_value(char **source, const size_t min, const size_t max);

size_t get_rand_number(const size_t min, const size_t max);

int generate(const char *path_output, const size_t sample_size, database_t *db);


