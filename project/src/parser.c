#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char *search_header(char *source, char const *key) {
    char *ptr_header = strcasestr(source, key);
    if (!ptr_header) {
        return NULL;
    }

    if (ptr_header == source) {
        return ptr_header + skip_space(ptr_header + strlen(key)) + strlen(key);
    }

    while (*(ptr_header - 1) != '\n') {
        char *skip_search = ptr_header + 1;
        ptr_header = strcasestr(skip_search, key);
    }

    return ptr_header + skip_space(ptr_header + strlen(key)) + strlen(key);
}

size_t check_next_str(char *source) {
    size_t i = 0;
    size_t k = 0;
    while (true) {
        if (*(source + i) == '@') {
            return true;
        }

        if (*(source + i) == '=') {
            return true;
        }

        if (*(source + i) == ':') {
            return false;
        }
        if (*(source + i) == '\r' || *(source + i) == '\n') {
            k++;

            if (k == 2) {
                return false;
            }
        }

        i++;
    }
}

char *parser_key_header(char *source, char const *key) {
    char *pos = search_header(source, key);

    char *value;

    if (!pos) {
        value = "";
        return value;
    }

    value = (char*)calloc(90000000, sizeof(char));

    size_t i = 0;
    size_t k = 0;
    while (true) {
        if (*(pos + i) == '\r' || *(pos + i) == '\n') {
            if (!check_next_str(pos + i + 1)) {
                return value;
            }
            i++;
        }
        if (*(pos + i) == '\r' || *(pos + i) == '\n') {
            i++;
        }
        *(value + k) = *(pos + i);
        i++;
        k++;
    }
}

char *get_boundary_key(char *source) {
    char *key_boundary = (char*)calloc(400, sizeof(char));;

    if (*source == '\"') {
        source++;
    }

    size_t i = 0;
    while (true) {
        if (*(source + i) == '\"' || *(source + i) == '\n' || *(source + i) == '\r') {
            break;
        }
        *(key_boundary + i) = *(source + i);
        i++;
    }

    return key_boundary;
}

size_t parser_key_parts(char *source) {
    size_t res = 1;

    char *pos_type = search_header(source, TYPE);
    if (!pos_type) {
        return res;
    }

    char* pos = strcasestr(pos_type, MULTIPART);
    if (!pos) {
        return res;
    }

    pos = strcasestr(pos, BOUNDARY);
    if (!pos || isalpha(*(pos - 1))) {
        return res;
    }

    if ((pos - pos_type) > MAX_LENGTH_COMPARE) {
        return res;
    }

    pos += strlen(BOUNDARY);

    char *key_boundary = get_boundary_key(pos);

    pos = strcasestr(pos, key_boundary);

    while (pos) {
        char *skip_search = pos + 1;
        pos = strcasestr(skip_search, key_boundary);

        if (pos && isspace(*(pos + strlen(key_boundary)))) {
            res++;
        }
    }
    return res - 1;
}

eml_t *parser(char *source) {
    eml_t *eml = calloc(sizeof(eml_t), 1);

    if (!eml) {
        return NULL;
    }

    eml->source = parser_key_header(source, FROM);
    eml->target = parser_key_header(source, TO);
    eml->date = parser_key_header(source, DATE);
    eml->parts = parser_key_parts(source);

    return eml;
}