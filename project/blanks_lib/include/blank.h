#pragma once //  NOLINT

#include <stddef.h>

#include <stdbool.h>

typedef struct node_blank {
    size_t number;

    struct node_blank *next;
    struct node_blank *prev;
} node_blank_t;

//  Add functional
void insert_node(node_blank_t *target, size_t number);
node_blank_t *push_front(node_blank_t *first, size_t number);
node_blank_t *push_back(node_blank_t *last, size_t number);

//  Output functional
node_blank_t *print_numbers_chain(node_blank_t *first);
