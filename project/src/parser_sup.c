#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <parser.h>

size_t check_zero_end(char const *source, char const *pos) {
    for (size_t i = strlen(source) - (pos - source); i > 0; i--) {
        if (!isspace(source[i])) {
            return i;
        }
    }
    return 0;
}

size_t skip_space(char *pos) {
    size_t i = 0;
    while (isspace(*pos++)) {
        i++;
    }
    return i;
}

char *rm_apst(char const *source) {
    char *res = (char*)calloc(strlen(source), sizeof(char));

    if (!res) {
        fprintf(stderr, "failed to allocate memory\n");
        return NULL;
    }

    size_t k = 0;
    for (size_t i = 1; i < strlen(source) - 1; i++) {
        res[k] = source[i];
        k++;
    }
    return res;
}