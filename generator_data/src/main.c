#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

#define NEEDED_COUNT_ARG 3

#define ERR_GENERATE -1
#define ERR_INPUT -2

#define SUCCESS 1

int main(int argc, const char **argv) {
    if (argc < NEEDED_COUNT_ARG) {
        fprintf(stderr, "incorrect input");
        return ERR_INPUT;
    }

    char* end = NULL;
    size_t sample_size  = strtoul(argv[1], &end, 0);
    if (*end != '\0') {
        fprintf(stderr, "incorrect input sample size");
        return ERR_INPUT;
    }

    if (!sample_size) {
        fprintf(stdout, "zero sample size");
        return SUCCESS;
    }

    const char *path_output = argv[2];

    int res = generate(path_output, sample_size);
    if (res < 0) {
        return ERR_GENERATE;
    }

    return SUCCESS;
}
