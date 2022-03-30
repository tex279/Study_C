#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stddef.h>

#include "utils.h"

#define MAX_AGE 100
#define MIN_AGE 18

#define MAX_SALARY 450000

#define LENGTH_STRING_FORMAT 10

#define ERR_OPEN_FILE -1
#define ERR_CLOSE_FILE -2

int generate(const char *path_output, const size_t sample_size, database_t *db) {
    FILE *target = fopen(path_output, "w+");
    if (!target) {
        fprintf(stderr, "error open file for write");
        return ERR_OPEN_FILE;
    }

    for (size_t i = 0; i < sample_size; ++i) {
        bool gender = (bool)get_rand_number(0, 1);
        bool type_surname = (bool)get_rand_number(0, 1);
        size_t age = get_rand_number(MIN_AGE, MAX_AGE);

        if (gender) {
            fprintf(target,"%s ", get_rand_value(db->set_female_name, 0, sizeof(db->set_female_name)));
        } else {
            fprintf(target,"%s ", get_rand_value(db->set_male_name, 0, sizeof(db->set_male_name)));
        }

        if (type_surname) {
            fprintf(target,"%s ", get_rand_value(db->set_surname, 0, sizeof(db->set_surname)));
        } else {
            if (gender) {
                fprintf(target,"%s ", get_rand_value(db->set_female_surname, 0, sizeof(db->set_female_surname)));
            } else {
                fprintf(target,"%s ", get_rand_value(db->set_male_surname, 0, sizeof(db->set_male_surname)));
            }

        }

        if (gender) {
            fprintf(target,"%s ", "female");
        } else {
            fprintf(target,"%s ", "male");
        }

        fprintf(target,"%zu ", age);

        fprintf(target,"%zu ", get_rand_number(0, MAX_SALARY));

        fprintf(target,"%s ", get_rand_value(db->set_position, 0, sizeof(db->set_position)));

        fprintf(target,"%zu\n",  get_rand_number(MIN_AGE, age));
    }


    if (fclose(target)) {
        fprintf(stderr, "failed close file");
        return ERR_CLOSE_FILE;
    }

    return 1;
}
