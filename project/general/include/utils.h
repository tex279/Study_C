#pragma once //  NOLINT

#include <stddef.h>

#define ERR_ALOCC -2

#define SUCCESS 1

char *create_str(const char *source);

char *create_format(const size_t size_str, const size_t size_format);
