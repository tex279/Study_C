#pragma once //  NOLINT

#include "../include/blank.h"
#include "../include/list_blanks.h"

#define ERR_OPEN -1

typedef struct node_list_parts {
    list_blanks_t *list_b;

    struct node_list_parts *next;
} node_list_parts_t;

node_list_parts_t *create_part(size_t number, char storage[], char responsible[]);

//  Data entry, structure filling
node_list_parts_t *input(char const *source, size_t *count_error);

//  Search combination storage and responsible in struct
node_list_parts_t *find_combination(node_list_parts_t *first, const char *storage, const char *responsible);

//  Output functional
void output_parts(node_list_parts_t* first, size_t *count_error);

//  Freeing Memory
void free_list_parts(node_list_parts_t* first);




