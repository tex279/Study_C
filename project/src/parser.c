#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <parser.h>

char *search_header(char *source, char const *key) {
    char *ptr_header = strcasestr(source, key);
    if (!ptr_header) {
        return NULL;
    }

    if (ptr_header == source) {
        return ptr_header + skip_space(ptr_header + strlen(key)) + strlen(key);
    }

    while (*(ptr_header - 1) != '\n') {
        ptr_header++;
        ptr_header = strcasestr(ptr_header, key);
    }

    return ptr_header + skip_space(ptr_header + strlen(key)) + strlen(key);
}

char* parser_key_header(char *source, char const *key) {
    char *pos = search_header(source, key);
    char *start = pos;

    if (!pos) {
        char *value = calloc(1, sizeof(char));
        if (!value) {
            return NULL;
        }
        return value;
    }

    while (true) {
        char *end = strchr(pos, '\r');
        if (!end) {
            end = strchr(pos, '\n');
        }

        pos = end;

        if (*end == '\n' && *(end + 1) == '\r') {
            end++;
        }
        if (*end == '\r' && *(end + 1) == '\n') {
            end++;
        }

        if (!check_str(end + 1)) {
            break;
        } else {
            pos = end + 1;
        }
    }

    char *value = get_value_header(pos, start);

    return value;
}

size_t parser_key_parts(char *source) {
    size_t res = 1;

    char *pos_type = search_header(source, TYPE);
    if (!pos_type) {
        return res;
    }

    char* pos_mul = strcasestr(pos_type, MULTIPART);
    if (!pos_mul) {
        return res;
    }

    char* pos = strcasestr(pos_mul, BOUNDARY);
    if (!pos || isalpha(*(pos - 1))) {
        return res;
    }

    if ((pos - pos_type) > MAX_LENGTH_COMPARE) {
        return res;
    }

    pos += strlen(BOUNDARY);

    char *key_boundary = get_boundary_key(pos);

    pos = strstr(pos, key_boundary);

    while (pos) {
        pos++;
        pos = strstr(pos, key_boundary);
        if (pos && isspace(*(pos + strlen(key_boundary)))) {
            res++;
        }
    }

    free(key_boundary);

    return res - 1;
}

eml_t *parser(char *source) {
    eml_t *eml = calloc(1, sizeof(eml_t));
    if (!eml) {
        return NULL;
    }

    eml->source = parser_key_header(source, FROM);
    eml->target = parser_key_header(source, TO);
    eml->date = parser_key_header(source, DATE);
    eml->parts = parser_key_parts(source);

    return eml;
}
