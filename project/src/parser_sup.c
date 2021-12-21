#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include <parser.h>

#define HEADER ':'

void free_eml(eml_t *eml) {
    free(eml->source);
    free(eml->target);
    free(eml->date);
    free(eml);
}

void print_eml(eml_t *eml) {
    fprintf(stdout, "%s|%s|%s|%zu\n", eml->source, eml->target, eml->date, eml->parts);
}

size_t skip_space(char *pos) {
    size_t i = 0;
    while (isspace(*pos++)) {
        i++;
    }
    return i;
}

size_t check_str(char *in) {
    if (in[0] == '\n' || in[0] == '\r') {
        return false;
    }

    size_t i = 1;

    size_t length_str = strlen(in);
    while (true) {
        if (in[i]  == HEADER) {
            return false;
        }

        if (in[i] == '\n' || in[i] == '\r') {
            char *new_in = in + (i + 1);

            if (!check_str(new_in)) {
                return true;
            }
        }

        if (i == length_str) {
            return false;
        }

        i++;
    }
}

char *get_value_header(char const *source, char const *end) {
    size_t length_value = end - source;

    char *value = calloc((length_value + 1), sizeof(char));
    if (!value) {
        return NULL;
    }

    size_t k = 0;
    size_t i = 0;
    while (k < length_value) {
        if (source[i] == '\n' ||source[i] == '\r') {
            i++;
            length_value--;
            continue;
        }
        value[k] = source[i];
        k++;
        i++;
    }

    value[length_value] = '\0';

    return value;
}

char *get_boundary_key(char *source) {
    if (*source == '\"') {
        source++;
    }

    size_t length_source = strlen(source);

    size_t i = 0;
    while (true) {
        if (i == length_source) {
            return NULL;
        }

        if (source[i] == '\"' || isspace(source[i])) {
            break;
        }
        i++;
    }

    size_t length_value = i;

    char *key_boundary = calloc(length_value + 1, sizeof(char));
    if (!key_boundary) {
        return NULL;
    }

    snprintf(key_boundary, length_value + 1, "%s", source);

    return key_boundary;
}
