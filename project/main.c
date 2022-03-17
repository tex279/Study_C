#include <stdio.h>
#include <stdlib.h>

#include "list_parts.h"

#define SUCCESS 0

int main(int argc, char const **argv) {
    if (argc != 2) {
        fprintf(stderr, "incorrect input");
        return -1;
    }

    char const *path_to_blk = argv[1];

    size_t count_error = 0;

    node_list_parts_t* first = input(path_to_blk, &count_error);

    output_parts(first, &count_error);

    free_list_parts(first);

    return SUCCESS;
}
