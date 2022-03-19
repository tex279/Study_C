#include <stdio.h>
#include <stdlib.h>

#include "../include/list_parts.h"

#define ERR_INPUT -1
#define ERR_WRONG_TYPE_WORK -2

#define IN_STD_OUT_STD 1
#define IN_FILE_OUT_STD 2
#define IN_STD_OUT_FILE 3
#define IN_FILE_OUT_FILE 4

#define SUCCESS 1

void work(char const *path_to_input_blk, char const *path_to_output_blk) {
    size_t count_error = 0;

    node_list_parts_t *first = input(path_to_input_blk, &count_error);


    output_parts(path_to_output_blk, first, &count_error);

    free_list_parts(first);
}

int main(int argc, char const **argv) {
    if (argc < 2) {
        fprintf(stderr, "incorrect input");
        return ERR_INPUT;
    }

    char* end = NULL;
    long type_work = strtol(argv[1], &end, 0);
    if (!end) {
        fprintf(stderr, "incorrect input type work");
        return ERR_INPUT;
    }

    switch (type_work) {
        case IN_STD_OUT_STD: {
            work(NULL, NULL);
            break;
        }
        case IN_FILE_OUT_STD: {
            work(argv[2], NULL);
            break;
        }
        case IN_STD_OUT_FILE: {
            work(NULL, argv[2]);
            break;
        }
        case IN_FILE_OUT_FILE: {
            work(argv[2], argv[3]);
            break;
        }
        default: {
            fprintf(stderr, "incorrect input type work: not such type");
            return ERR_WRONG_TYPE_WORK;
        }
    }

    return SUCCESS;
}
