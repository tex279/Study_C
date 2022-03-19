#pragma once //  NOLINT

#include <errno.h>
#include <stdio.h>

#define FATAL(message) do {                 \
    if (errno) {                            \
        perror(message);                    \
    } else {                                \
        fprintf(stderr, "%s\n", message);   \
    }                                       \
    exit(1);                                \
} while (0)

#define ASSERT(condition, message) do {     \
    if (!(condition))                       \
        FATAL(message);                     \
} while (0)

#define ERR_ALOC -2

#define SUCCESS 1

char *create_str(const char *source);
