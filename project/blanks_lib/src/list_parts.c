#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list_parts.h"
#include "utils.h"

#define LENGTH_NUMBER 8
#define LENGTH_STORAGE 80
#define LENGTH_RESPONSIBLE 80

#define LENGTH_STRING_FORMAT 10

node_list_parts_t *find_combination(node_list_parts_t *first, const char *storage, const char *responsible) {
    node_list_parts_t *tmp = first;

    while (tmp != NULL) {
        if ((strcmp(tmp->list_b->storage, storage) == 0) &&
            (strcmp(tmp->list_b->responsible, responsible) == 0)) {
            return tmp;
        }

        tmp = tmp->next;
    }

    return NULL;
}

node_list_parts_t *create_part(const size_t number, char *storage, char *responsible) {
    node_list_parts_t *tmp_part = calloc(1, sizeof(node_list_parts_t));
    if (!tmp_part) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    tmp_part->list_b = create_list(number, storage, responsible);
    if (!tmp_part->list_b) {
        free(tmp_part);
        return NULL;
    }

    tmp_part->next = NULL;

    return tmp_part;
}

int input(char const *source, size_t *count_error, node_list_parts_t **first1) {
    FILE *target = stdin;

    if (source) {
        target = fopen(source, "r");
        ASSERT(target, "failed open file for read");
    }

    node_list_parts_t *first = NULL;
    node_list_parts_t *last = NULL;

    char global[LENGTH_NUMBER + LENGTH_STORAGE + LENGTH_RESPONSIBLE + 1];

    while (!feof(target)) {
        fgets(global, sizeof(global), target);
        if (strlen(global) == 0) {
            break;
        }

        size_t numb = 0;
        char buf_number[LENGTH_NUMBER + 1];
        char format_string_number[LENGTH_STRING_FORMAT + 1];
        snprintf(format_string_number, LENGTH_STRING_FORMAT + 1, "%%%ds", LENGTH_NUMBER);
        if (sscanf(global, format_string_number, buf_number) == 1) {
            char *end;
            numb = strtoul(buf_number, &end, 0);
            if (strlen(end)) {
                (*count_error)++;
                continue;
            }
        }
        size_t indent = strlen(buf_number);


        char buf_storage[LENGTH_STORAGE + 1];
        char format_string_storage[LENGTH_STRING_FORMAT + 1];
        snprintf(format_string_storage, LENGTH_STRING_FORMAT + 1, "%%%ds", LENGTH_STORAGE);
        if (sscanf(&global[indent], format_string_storage, buf_storage) != 1) {
            (*count_error)++;
            continue;
        }
        indent += strlen(buf_storage) + 1;

        char buf_responsible[LENGTH_RESPONSIBLE + 1];
        char format_string_responsible[LENGTH_STRING_FORMAT + 1];
        snprintf(format_string_responsible, LENGTH_STRING_FORMAT + 1, "%%%ds", LENGTH_RESPONSIBLE);
        if (sscanf(&global[indent], format_string_responsible, buf_responsible) != 1) {
            (*count_error)++;
            continue;
        }


        if (!first) {
            node_list_parts_t *check_create = create_part(numb, buf_storage, buf_responsible);
            if (!check_create) {
                return ERR_ALOC;
            }

            first = check_create;
            last = check_create;
            continue;
        }

        node_list_parts_t *cur_part = find_combination(first, buf_storage, buf_responsible);
        if (cur_part) {
            if (!insert(cur_part->list_b, numb)) {
                free_list_parts(first);
                return ERR_ALOC;
            }
        } else {
            node_list_parts_t *tmp_part = create_part(numb, buf_storage, buf_responsible);

            last->next = tmp_part;

            last = tmp_part;
        }
    }

    *first1 = first;

    ASSERT(!fclose(target), "failed close file");

    return 1;
}

void output_parts(char const *target, node_list_parts_t *first, size_t *count_error) {
    FILE *stream_in = stdout;

    if (target) {
        stream_in = fopen(target, "w+");
        ASSERT(target, "failed create file for write");
    } else {
        fprintf(stream_in, "\nResult:\n");
    }

    node_list_parts_t *iterator = first;

    while (iterator) {
        print_list(stream_in, iterator->list_b);

        iterator = iterator->next;
    }

    if (*count_error) {
        fprintf(stream_in, "%zu\n", *count_error);
    }

    if (target) {
        ASSERT(!fclose(stream_in), "failed close file");
    }
}

void free_list_parts(node_list_parts_t *first) {
    while (first) {
        free_list_blank(first->list_b);

        node_list_parts_t *iterator = first;

        first = first->next;

        free(iterator);
    }

    free(first);
}
