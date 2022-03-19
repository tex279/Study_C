#pragma once //  NOLINT

#include <stdio.h>

typedef struct node_blank {
    size_t number;

    struct node_blank *next;
    struct node_blank *prev;
} node_blank_t;

//  Add functional
node_blank_t *insert_node(node_blank_t *target, const size_t number);
node_blank_t *push_front(node_blank_t *first, const size_t number);
node_blank_t *push_back(node_blank_t *last, const size_t number);

//  Output functional
node_blank_t *print_numbers_chain(FILE *stream, node_blank_t *first);
