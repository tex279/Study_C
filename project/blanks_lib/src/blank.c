#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "blank.h"
#include "utils.h"

node_blank_t *insert_node(node_blank_t *target, const size_t number) {
    node_blank_t *tmp = calloc(1, sizeof(node_blank_t));
    ASSERT(tmp, "failed get memory");

    tmp->number = number;

    tmp->next = target;
    tmp->prev = target->prev;

    target->prev->next = tmp;
    target->prev = tmp;

    return tmp;
}

node_blank_t *push_front(node_blank_t *first, const size_t number) {
    node_blank_t *tmp = calloc(1, sizeof(node_blank_t));
    ASSERT(tmp, "failed get memory");

    tmp->number = number;

    tmp->next = first;
    tmp->prev = first->prev;

    first->prev = tmp;

    return tmp;
}

node_blank_t *push_back(node_blank_t *last, const size_t number) {
    node_blank_t *tmp = calloc(1, sizeof(node_blank_t));
    ASSERT(tmp, "failed get memory");

    tmp->number = number;

    tmp->prev = last;
    tmp->next = last->next;

    last->next = tmp;

    return tmp;
}

node_blank_t *print_numbers_chain(FILE *stream, node_blank_t *first) {
    node_blank_t *iterator = first;

    while (iterator->next) {
        if (iterator->next->number > (iterator->number + 1)) {
            break;
        }
        fprintf(stream, "%zu ", iterator->number);

        iterator = iterator->next;
    }

    fprintf(stream, "%zu\n", iterator->number);

    return iterator;
}
