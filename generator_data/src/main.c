#include <stdio.h>
#include <stdlib.h>

#include "generator.h"
#include "utils.h"

#define NEEDED_COUNT_ARG 8

#define ERR_GENERATE -1
#define ERR_INPUT -2
#define LOAD_DATA -4

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

    database_t *db = load_data(argv, 2);
    if (!db) {
        fprintf(stderr, "error load data");
        return LOAD_DATA;
    }

    const char *path_output = argv[2];

    int res = generate(path_output, sample_size, db);
    if (res < 0) {
        return ERR_GENERATE;
    }

    free_database(db);

    return EXIT_SUCCESS;
}
