#pragma once //  NOLINT

#include "../include/blank.h"

typedef struct list_blanks {
    node_blank_t *first;
    node_blank_t *last;

    char *storage;
    char *responsible;
} list_blanks_t;

list_blanks_t *create_list(size_t number, char *storage, char *responsible);

//  Determining rule for inserting a new link
void insert(list_blanks_t* target, size_t number);

//  Output functional
void print_list(list_blanks_t *list_b);

//  Freeing Memory
void free_list_blank(list_blanks_t *list_b);
