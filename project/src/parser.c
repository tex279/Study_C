#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <parser.h>

char *search_value(char const *source, char const *key) {
    char str_key[sizeof(key)];
    snprintf(str_key, sizeof(str_key), "%s", key);
    char *res = strstr(source, str_key);
    if (!res) {
        return NULL;
    }
    return res;
}

char *get_pos(char const *source, char const *key, char *res) {
    if ((res - source) == 0) {
        return res + skip_space(res) + strlen(key) + 1;
    }
    return NULL;
}

char *get_value(char const *source, char const *pos) {
    char *res = (char*)calloc(strlen(source), sizeof(char));

    if (!res) {
        fprintf(stderr, "failed to allocate memory\n");
        return NULL;
    }

    size_t end_str = check_zero_end(source, pos);
    for (size_t i = 0; i < end_str; i++) {
        if (source[pos - source + i] == '\n' || source[pos - source + i] == '\r') {
            continue;
        }
        res[i] = source[pos - source + i];
    }
    return res;
}


char *parser_key(char const *str, char const *key) {
    char *pos = search_value(str, key);
    if (pos) {
        pos = get_pos(str, key, pos);
    }
    if (pos) {
        char* data = get_value(str, pos);
        return data;
    }
    return NULL;
}

int parser(FILE *filename) {
    eml_t *data = create_eml();

    size_t i = 1;
    char *starus_b = NULL;

    while (!feof(filename)) {
        char str[MAX_LENGTH_STR];
        fgets(str, sizeof(str), filename);

        if (!data->source) {
            data->source = parser_key(str, FROM);
        }
        if (!data->target) {
            data->target = parser_key(str, TO);
        }
        if (!data->date) {
            data->date = parser_key(str, DATE);
        }
        if (data->source != NULL && data->target != NULL && data->date != NULL) {
            break;
        }

        if (!starus_b) {
            starus_b = check_type_eml(str);
            //  fprintf(stdout, "%s\n", starus_b);
        }

        if (starus_b) {
            // fprintf(stdout, "%s88888888888888888888888888\n", starus_b);
            if (search_value(str, starus_b)) {
                i++;
            }
        }


        data->part = i;
    }
    output(data);
    free_eml(data);
    return EXIT_SUCCESS;
}

char *check_type_eml(char const *str) {
    if (search_value(str, TYPE)) {
        if (search_value(str, MULTIPART)) {
            char *pos = search_value(str, BOUNDARY);
            if (pos) {
                char *key_part = get_value(str, pos + strlen(BOUNDARY));
                if (key_part[0] == '\"') {
                    key_part = rm_apst(key_part);
                    return key_part;
                }
                return key_part;
            }
            return NULL;
        }
        return NULL;
    }
    return NULL;
}
