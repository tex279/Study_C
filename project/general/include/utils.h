#pragma once //  NOLINT

#include <stddef.h>

#define ERR_OPEN_FILE -1
#define ERR_CREATE_FILE -2
#define ERR_WRITE_FILE -3
#define ERR_CLOSE_FILE -4

#define ERR_ALOCC -2

char *create_str(const char *source);

char *create_format(const size_t size_str, const size_t size_format);
