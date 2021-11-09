#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include <parser.h>

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

size_t check_str(char const *in) {
    size_t i = 0;
    while (true) {
        if (*(in + i) == ':') {
            return false;
        }

        if (*(in + i) == '=') {
            return true;
        }

        if (*(in + i) == '@') {
            return true;
        }
        if (*(in + i) == '\n' || *(in + i) == '\r') {
            return false;
        }
        i++;
    }
}

char *get_value_header(char const *end, char *start) {
    size_t length_value = (size_t)(end - start);

    char *value = calloc((length_value + 1), sizeof(char));
    if (!value) {
        return NULL;
    }

    size_t k = 0;
    size_t i = 0;
    while (k < length_value) {
        if (*(start + i) == '\n' || *(start + i) == '\r') {
            i++;
            length_value--;
            continue;
        }
        *(value + k) = *(start + i);
        k++;
        i++;
    }
    *(value + length_value) = '\0';

    return value;
}

char *get_boundary_key(char *source) {
    if (*source == '\"') {
        source++;
    }

    size_t i = 0;
    while (true) {
        if (*(source + i) == '\"' || isspace(*(source + i))) {
            break;
        }
        i++;
    }

    size_t length_value = i;

    char *key_boundary = calloc(length_value + 1, sizeof(char));;

    size_t k = 0;
    while (k < length_value) {
        *(key_boundary + k) = *(source + k);
        k++;
    }

    *(key_boundary + length_value) = '\0';
    return key_boundary;
}
