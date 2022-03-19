#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "list_blanks.h"
#include "utils.h"

list_blanks_t *create_list(const size_t number, char *storage, char *responsible) {
    list_blanks_t *tmp_list = calloc(1, sizeof(list_blanks_t));
    if (!tmp_list) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    tmp_list->storage = create_str(storage);
    if (!tmp_list->storage) {
        free(tmp_list);
        return NULL;
    }

    tmp_list->responsible = create_str(responsible);
    if (!tmp_list->responsible) {
        free(tmp_list->storage);
        free(tmp_list);
        return NULL;
    }

    node_blank_t *tmp_blank = calloc(1, sizeof(node_blank_t));
    if (!tmp_blank) {
        free(tmp_list->storage);
        free(tmp_list->responsible);
        free(tmp_list);
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    tmp_blank->number = number;

    tmp_list->first = tmp_blank;
    tmp_list->last = tmp_blank;

    return tmp_list;
}

node_blank_t *insert(list_blanks_t *target, const size_t number) {
    if (target->first->number >= number) {
        target->first = push_front(target->first, number);
        return target->first;
    }

    if (target->last->number <= number) {
        target->last = push_back(target->last, number);
        return target->last;
    }

    node_blank_t *iterator = target->first->next;

    while (iterator != NULL) {
        if (number < iterator->number) {
            return insert_node(iterator, number);
        }

        iterator = iterator->next;
    }

    return NULL;
}

int print_list(FILE *stream, const list_blanks_t *list_b) {
    fprintf(stream, "%s %s\n", list_b->storage, list_b->responsible);

    node_blank_t *end_chain = print_numbers_chain(stream, list_b->first);

    while (end_chain->next) {
        fprintf(stream, "%s %s\n", list_b->storage, list_b->responsible);

        end_chain = print_numbers_chain(stream, end_chain->next);
    }

    return SUCCESS;
}

int free_list_blank(list_blanks_t *list_b) {
    while (list_b->first != NULL) {
        node_blank_t* tmp = list_b->first;

        list_b->first = list_b->first->next;

        free(tmp);
    }

    free(list_b->storage);
    free(list_b->responsible);

    free(list_b);

    return SUCCESS;
}
