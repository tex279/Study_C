#include <stdio.h>
#include <stdlib.h>

#include "../include/list_parts.h"

#define SUCCESS 0

#define STDOUT 2

#define FILE 3

int main(int argc, char const **argv) {
    if (argc > 3) {
        fprintf(stderr, "incorrect input");
        return -1;
    }

    char const *path_to_input_blk = argv[1];

    char const *path_to_output_blk = NULL;

    if (argc == 3) {
        path_to_output_blk = argv[2];
    }

    size_t count_error = 0;

    node_list_parts_t* first = input(path_to_input_blk, &count_error);

    output_parts(path_to_output_blk, first, &count_error);

    free_list_parts(first);

    return SUCCESS;
}
