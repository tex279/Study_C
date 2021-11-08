#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <parser.h>

size_t check_header(char const *source, size_t const pos) {
    if (pos == 0 || source[pos - 1] == '\n' || source[pos - 1] == '\r') {
        return true;
    }
    return false;
}

int search_header(char const *source, char const *key) {
    int pos = 0;
    pos = search(pos, source, key);
    if (!pos) {
        return pos;
    }
    if (pos == -1) {
        return -1;
    }
    while (!check_header(source, pos)) {
        pos += strlen(key);
        pos = search(pos, source, key);
    }
    return pos;
}

char *parser_key_header(char const *source, char const *key, size_t const flag_rule) {
    int pos = search_header(source, key);
    if (pos == -1) {
        char *value;
        value = "";
        return value;
    }
    char *value = get_value(source, pos + strlen(key) + skip_space(source, pos + strlen(key)));
    if (!value) {
        return NULL;
    }

    if (flag_rule) {
        if (!strchr(value, '@')) {
            pos = search(pos, source, "\n");
            char *more_value = get_value(source, pos + 1);
            value = strncat(value, more_value, strlen(more_value));
        }
    }

    return value;
}

size_t parser_key_parts(char const *source) {
    size_t res = 1;
    int pos = search_header(source, TYPE);
    if (pos != -1) {
        pos = search(pos, source, MULTIPART);
        if (pos != -1) {
            pos = search(pos, source, BOUNDARY);
            if (pos != -1) {
                char *key_part = get_value(source, pos + strlen(BOUNDARY));
                //  fprintf(stdout, "MAIN    %s\n", key_part);
                if (key_part[0] == '\"') {
                    key_part = rm_aptr(key_part);
                }
                //  fprintf(stdout, "MAIN    %s\n", key_part);
                res = 0;
                pos = search(pos, source, key_part);
                /*for (size_t i = 0; i < 100; i++) {
                    fprintf(stdout, "%c", source[pos - 10 +i]);
                }*/
                while (pos != -1) {
                    //  fprintf(stdout, "FIND\n");
                    if (source[pos + strlen(key_part)] != '-') {
                        res++;
                    }
                    //  fprintf(stdout, "FIND\n");
                    //  fprintf(stdout, "-----%c----\n", source[pos]);
                    if (source[pos + strlen(key_part)] == '-') {
                        break;
                    }
                    //  fprintf(stdout, "%ld\n", res);
                    pos += strlen(key_part);
                    pos = search(pos, source, key_part);
                    //  fprintf(stdout, "!----%c----!", source[pos + strlen(key_part)]);
                    //  fprintf(stdout, "\n");
                }
                if (res > 1) {
                    res = res - 1;
                }
            }
        }
    }
    return res;
}

eml_t *parser(char const *source) {
    eml_t *eml = calloc(sizeof(eml_t), 1);

    if (!eml) {
        return NULL;
    }

    eml->source = parser_key_header(source, FROM, 1);
    eml->target = parser_key_header(source, TO, 1);
    eml->date = parser_key_header(source, DATE, 0);
    eml->parts = parser_key_parts(source);

    return eml;
}