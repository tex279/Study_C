#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list_parts.h"
#include "utils.h"

#define LENGTH_NUMBER 8
#define LENGTH_STORAGE 80
#define LENGTH_RESPONSIBLE 80

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

node_list_parts_t *create_part(size_t number, char *storage, char *responsible) {
    node_list_parts_t *tmp_part = calloc(1, sizeof(node_list_parts_t));
    ASSERT(tmp_part, "failed get memory");

    tmp_part->list_b = create_list(number, storage, responsible);

    tmp_part->next = NULL;

    return tmp_part;
}

node_list_parts_t *input(char const *source, size_t *count_error) {
    FILE *target = fopen(source, "r");
    ASSERT(target, "failed open file for read");

    node_list_parts_t *first = NULL;
    node_list_parts_t *last = NULL;

    char global[LENGTH_NUMBER + LENGTH_STORAGE + LENGTH_RESPONSIBLE + 1];

    while (!feof(target)) {
        fgets(global, sizeof(global), target);
        if (strlen(global) == 1) {
            break;
        }

        char *number = scan_data(global, LENGTH_NUMBER);
        if (!number) {
            (*count_error)++;
            continue;
        }
        size_t indent  = strlen(number);

        char *end;
        size_t numb = strtoul(number, &end, 0);
        if (strlen(end)) {
            free(number);
            (*count_error)++;
            continue;
        }
        free(number);

        char *storage = scan_data(&global[indent], LENGTH_STORAGE);
        if (!storage) {
            (*count_error)++;
            continue;
        }
        indent += strlen(storage) + 1;

        char *responsible = scan_data(&global[indent], LENGTH_RESPONSIBLE);
        if (!responsible) {
            free(storage);
            (*count_error)++;
            continue;
        }

        if (!first) {
            first = create_part(numb, storage, responsible);
            last = first;
        } else {
            node_list_parts_t *cur_part = find_combination(first, storage, responsible);

            if (cur_part) {
                insert(cur_part->list_b, numb);

                free(storage);
                free(responsible);
            } else {
                node_list_parts_t *tmp_part = create_part(numb, storage, responsible);
                last->next = tmp_part;

                last = tmp_part;
            }
        }
    }

    ASSERT(!fclose(target), "failed close file");

    return first;
}

void output_parts(node_list_parts_t *first, size_t *count_error) {
    node_list_parts_t *iterator = first;

    while (iterator) {
        print_list(iterator->list_b);

        iterator = iterator->next;
    }

    if (*count_error) {
        fprintf(stdout, "%zu\n", *count_error);
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