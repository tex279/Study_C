#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_LENGTH_BUF 80

#define LENGTH_STRING_FORMAT 10

char *create_str(char *source) {
    size_t len = strlen(source);

    char *tmp = calloc(len + 1, sizeof(char));
    ASSERT(tmp, "failed get memory");

    tmp = strncpy(tmp, source, len);

    tmp[len] = '\0';

    return tmp;
}

char *scan_data(char *source, size_t size_str_data) {
    char *out = NULL;

    char buf[MAX_LENGTH_BUF + 1] = {};

    char format_string[LENGTH_STRING_FORMAT + 1] = {};

    snprintf(format_string, LENGTH_STRING_FORMAT + 1, "%%%zus", size_str_data);

    if (sscanf(source, format_string, buf) == -1) {
        return NULL;
    }

    out = create_str(buf);

    return out;
}
