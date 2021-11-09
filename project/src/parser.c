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

char* parser_key_header(char *source, char const *key) {
    char *pos = search_header(source, key);
    char *start;
    start = pos;

    if (!pos) {
        char *value = calloc(1, sizeof(char));
        return value;
    }

    while (true) {
        char *end = strchr(pos, '\r');
        if (!end) {
            end = strchr(pos, '\n');
        }

        pos = end - 1;

        if (*end == '\n' && *(end + 1) == '\r') {
            end++;
        }
        if (*end == '\r' && *(end + 1) == '\n') {
            end++;
        }

        if (!check_str(end + 1)) {
            break;
        }

        pos = end + 1;
    }

    size_t length_value = (size_t)(pos - start + 1);

    char *value = (char*)calloc((length_value + 1), sizeof(char));

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
    *(value + length_value + 1) = '\0';
    return value;
}

char *get_boundary_key(char *source) {
    if (*source == '\"') {
        source++;
    }

    size_t i = 0;
    while (true) {
        if (*(source + i) == '\"' || *(source + i) == '\n' || *(source + i) == '\r') {
            break;
        }
        i++;
    }

    size_t length_value = i;

    char *key_boundary = (char*)calloc(length_value + 1, sizeof(char));;

    size_t k = 0;
    while (k < length_value) {
        *(key_boundary + k) = *(source + k);
        k++;
    }

    *(key_boundary + length_value + 1) = '\0';
    return key_boundary;
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
        char *skip_search = pos + 1;
        pos = strstr(skip_search, key_boundary);

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
