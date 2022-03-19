#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_LENGTH_BUF 80

#define LENGTH_STRING_FORMAT 10

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
