#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "utils.h"

#define MAX_AGE 100
#define MIN_AGE 18

#define MIN_EXP 0

#define MAX_SALARY 450000

#define LENGTH_STRING_FORMAT 10

#define ERR_OPEN_FILE -1
#define ERR_CLOSE_FILE -2

size_t get_rand_number(const size_t min, const size_t max) {
    return (min + (size_t)rand() % (max - min + 1));
}

char *get_rand_value(char **source, const size_t min, const size_t max) {
    return source[get_rand_number(min, max)];
}


int generate(const char *path_output, const size_t sample_size, const database_t *db) {
    FILE *target = fopen(path_output, "w+");
    if (!target) {
        fprintf(stderr, "error open file for write");
        return ERR_OPEN_FILE;
    }

    fprintf(target,"%zu\n", sample_size);

    fprintf(target,"%zu\n", db->count_position + 1);

    for (size_t i = 0; i < sample_size; ++i) {
        bool gender = (bool)get_rand_number(0, 1);

        //
        bool type_surname = (bool)get_rand_number(0, 1);

        size_t age = get_rand_number(MIN_AGE, MAX_AGE);

        //  name
        if (gender) {
            fprintf(target,"%s ", get_rand_value(db->set_female_name, 0, db->count_female_name));
        } else {
            fprintf(target,"%s ", get_rand_value(db->set_male_name, 0, db->count_male_name));
        }

        //  surname
        if (type_surname) {
            fprintf(target,"%s ", get_rand_value(db->set_surname, 0, db->count_surname));
        } else {
            if (gender) {
                fprintf(target,"%s ", get_rand_value(db->set_female_surname, 0, db->count_female_surname));
            } else {
                fprintf(target,"%s ", get_rand_value(db->set_male_surname, 0, db->count_male_surname));
            }

        }

        //  gender
        if (gender) {
            fprintf(target,"%s ", "female");
        } else {
            fprintf(target,"%s ", "male");
        }

        //  age
        fprintf(target,"%zu ", age);

        //  salary
        fprintf(target,"%zu ", get_rand_number(0, MAX_SALARY));

        //  position(job)
        fprintf(target,"%s ", get_rand_value(db->set_position, 0, db->count_position));

        //  experience
        fprintf(target,"%zu\n",  get_rand_number(MIN_EXP, age - MIN_AGE));
    }

    if (fclose(target)) {
        fprintf(stderr, "failed close file");
        return ERR_CLOSE_FILE;
    }

    return SUCCESS;
}
