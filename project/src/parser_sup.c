#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <parser.h>

size_t skip_space(char const *source, size_t const pos) {
    size_t k = 0;
    while (isspace(source[pos + k])) {
        k++;
    }
    return k;
}

int cmp_str(size_t const begin, char const *source, char const *key) {
    for (size_t k = 0; k < strlen(key); k++) {
        if (toupper(source[begin + k]) != toupper(key[k])) {
            return false;
        }
    }
    return true;
}

int search(size_t const begin, char const *source, char const *key) {
    for (size_t i = begin; i < strlen(source); i++) {
        if (cmp_str(i, source, key)) {
            return i;
        }
    }
    return -1 ;
}

char *get_value(char const *source, size_t const pos) {
    char *res = create_str(MAX_LENGTH_STR);

    for (size_t i = 0; i < MAX_LENGTH_STR; i++) {
        if (source[pos + i] == '\n' || source[pos + i] == '\r') {
            break;
        }
        res[i] = source[pos + i];
    }
    return res;
}

char *rm_aptr(char const *value) {
    char *res = create_str(strlen(value) - 2);
    for (size_t i = 0; i < strlen(value); i++) {
        if (value[i + 1] == '\"') {
            break;
        }
        res[i] = value[i + 1];
    }
    return res;
}

char *create_str(size_t const length) {
    char *res = (char*)calloc(length, sizeof(char));
    if (!res) {
        fprintf(stderr, "failed to allocate memory\n");
        return NULL;
    }
    return res;
}