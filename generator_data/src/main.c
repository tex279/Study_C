#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

#include "utils.h"

#define NEEDED_COUNT_ARG 3

#define ERR_GENERATE -1
#define ERR_INPUT -2

#define SUCCESS 0

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

    database_t db;

    db.set_female_name = get_set(argv[3]);
    db.set_male_name = get_set(argv[4]);
    db.set_surname = get_set(argv[5]);
    db.set_female_surname = get_set(argv[6]);
    db.set_male_surname = get_set(argv[7]);
    db.set_position = get_set(argv[8]);

    const char *path_output = argv[2];

    int res = generate(path_output, sample_size, &db);
    if (res < 0) {
        return ERR_GENERATE;
    }

    free_set(db.set_female_name);
    free_set(db.set_male_name);
    free_set(db.set_surname);
    free_set(db.set_female_surname);
    free_set(db.set_male_surname);
    free_set(db.set_position);


    return SUCCESS;
}
