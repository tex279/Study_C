#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list_parts.h"
#include "utils.h"

#define LENGTH_NUMBER 8
#define LENGTH_STORAGE 80
#define LENGTH_RESPONSIBLE 80

#define LENGTH_STRING_FORMAT 10

#define ERR_OPEN_FILE -1
#define ERR_CREATE_FILE -2
#define ERR_WRITE_FILE -3
#define ERR_CLOSE_FILE -4

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
        if (!target) {
            fprintf(stderr, "error open file for read");
            return ERR_OPEN_FILE;
        }
    }

    node_list_parts_t *first = NULL;
    node_list_parts_t *last = NULL;

    char *format_number = create_format(LENGTH_NUMBER, LENGTH_STRING_FORMAT);
    if (!format_number) {
        return ERR_ALOC;
    }

    char *format_storage = create_format(LENGTH_STORAGE, LENGTH_STRING_FORMAT);
    if (!format_storage) {
        return ERR_ALOC;
    }
    char *format_responsible = create_format(LENGTH_RESPONSIBLE, LENGTH_STRING_FORMAT);
    if (!format_responsible) {
        return ERR_ALOC;
    }

    char global[LENGTH_NUMBER + LENGTH_STORAGE + LENGTH_RESPONSIBLE + 1];

    while (!feof(target)) {
        fgets(global, sizeof(global), target);

        size_t numb = 0;
        char buf_number[LENGTH_NUMBER + 1];
        if (sscanf(global, format_number, buf_number) == 1) {
            char *end;
            numb = strtoul(buf_number, &end, 0);
            if (strlen(end)) {
                (*count_error)++;
                continue;
            }
        }
        size_t indent = strlen(buf_number);


        char buf_storage[LENGTH_STORAGE + 1];
        if (sscanf(&global[indent], format_storage, buf_storage) != 1) {
            (*count_error)++;
            continue;
        }
        indent += strlen(buf_storage) + 1;

        char buf_responsible[LENGTH_RESPONSIBLE + 1];
        if (sscanf(&global[indent], format_responsible, buf_responsible) != 1) {
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
            if (!tmp_part) {
                free_list_parts(first);
                return ERR_ALOC;
            }

            last->next = tmp_part;

            last = tmp_part;
        }
    }

    free(format_number);
    free(format_storage);
    free(format_responsible);

    *first1 = first;

    if (fclose(target)) {
        fprintf(stderr, "failed close file");
        return ERR_CLOSE_FILE;
    }

    return SUCCESS;
}

int output_parts(char const *target, node_list_parts_t *first, size_t *count_error) {
    FILE *stream_in = stdout;

    if (target) {
        stream_in = fopen(target, "w+");
        if (!stream_in) {
            fprintf(stderr, "failed create file for write");
            return ERR_OPEN_FILE;
        }
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
        if (fclose(stream_in)) {
            fprintf(stderr, "failed close file");
            return ERR_CLOSE_FILE;
        }
    }

    return SUCCESS;
}

int free_list_parts(node_list_parts_t *first) {
    while (first) {
        free_list_blank(first->list_b);

        node_list_parts_t *iterator = first;

        first = first->next;

        free(iterator);
    }

    free(first);

    return SUCCESS;
}
