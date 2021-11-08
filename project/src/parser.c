#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <parser.h>

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
        return ptr_header + skip_space(ptr_header) + strlen(key) + 1;
    }

    while (*(ptr_header - 1) != '\n') {
        char *skip_search = ptr_header + 1;
        ptr_header = strcasestr(skip_search, key);
    }

    return ptr_header + skip_space(ptr_header) + strlen(key) + 1;
}

int check_end_header(char *source) {
    if (*source == '\n' || *source == '\r') {
        for (size_t i = 2; i < BUF; i++) {
            if (*(source + i) == '\n' || *(source + i) == '\r') {
                return false;
            }
            if (*(source + i) == ':') {
                return true;
            }
        }
    }
    return false;
}

char *parser_key_header(char *source, char const *key) {
    char *pos = search_header(source, key);

    char *value = (char*)calloc(400, sizeof(char));

    if (!pos) {
        value = "";
        return value;
    }
    size_t i = 0;
    size_t k = 0;
    while (!check_end_header(pos + i)) {
        if (*(pos + i) == '\n' || *(pos + i) == '\r') {
            i++;
        }
        *(value + k) = *(pos + i);
        i++;
        k++;
    }
    return value;
}

size_t parser_key_parts(char *source) {
    size_t res = 1;
    char *pos = search_header(source, TYPE);
    if (pos) {
        pos = strcasestr(pos, MULTIPART);
        //  fprintf(stdout, "FIND\n");
        if (pos) {
            pos = strcasestr(pos, BOUNDARY);
            //  fprintf(stdout, "FIND\n");
            if (pos) {
                pos += strlen(BOUNDARY);

                char *key_boundary = (char*)calloc(400, sizeof(char));;

                if (*pos == '\"') {
                    pos++;
                }
                //  fprintf(stdout, "FIND\n");
                size_t i = 0;
                while (true) {
                    if (*(pos + i) == '\"' || *(pos + i) == '\n' || *(pos + i) == '\r' || *(pos + i) == ':') {
                        break;
                    }
                    *(key_boundary + i) = *(pos + i);
                    i++;
                }
                //  fprintf(stdout, "%s\n", key_boundary);
                pos = strcasestr(pos, key_boundary);
                while (pos) {
                    //  fprintf(stdout, "FIND\n");
                    char *skip_search = pos + 1;
                    pos = strcasestr(skip_search, key_boundary);
                    if (pos && *(pos + strlen(key_boundary)) != '-') {
                        //  fprintf(stdout, "FIND\n");
                        res++;
                    }
                }
                res = res - 1;
            }
        }
    }
    return res;
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