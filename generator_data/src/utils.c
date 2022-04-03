#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

char *create_str(const char *source) {
    size_t len = strlen(source);

    char *tmp = calloc(len + 1, sizeof(char));
    if (!tmp) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    tmp = strncpy(tmp, source, len);

    tmp[len] = '\0';

    return tmp;
}

char *create_format(const size_t size_str, const size_t size_format) {
    char *format = calloc(size_format + 1, sizeof(char));
    if (!format) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    snprintf(format, size_format + 1, "%%%zus", size_str);

    return format;
}
