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
        fprintf(stderr, ERR_INPUT_M);
        return ERR_INPUT;
    }

    char* end = NULL;
    size_t sample_size  = strtoul(argv[1], &end, 0);
    if (*end != '\0') {
        fprintf(stderr, ERR_CONVERSION_M);
        return ERR_INPUT;
    }

    database_t *db = load_data(argv, 2);
    if (!db) {
        fprintf(stderr, ERR_LOAD_DATA_M);
        return LOAD_DATA;
    }

    const char *path_output = argv[2];

    int res = generate(path_output, sample_size, db);
    if (res < 0) {
        fprintf(stderr, ERR_GENERATE_M);
        return ERR_GENERATE;
    }

    free_database(db);

    return EXIT_SUCCESS;
}
