#pragma once //  NOLINT

#include <errno.h>
#include <stdio.h>

#define FATAL(message) do {                 \
    if (errno)                              \
        perror(message);                    \
    else                                    \
        fprintf(stderr, "%s\n", message);   \
    exit(1);                                \
} while (0)

#define ASSERT(condition, message) do {     \
    if (!(condition))                       \
        FATAL(message);                     \
} while (0)

char *create_str(char *source);

char *scan_data(char *source, size_t size_str_data);
