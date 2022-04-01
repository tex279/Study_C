#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "database_functional.h"

#define MAX_AGE 100
#define MIN_AGE 18

void get_average_salary_report(const database_t *db) {
    size_t number_records = db->number_records;

    size_t number_positions = db->number_positions;

    //fprintf(stdout,"%zu %zu\n", number_records, number_positions);

    size_t **distribution  = calloc(number_positions, sizeof(size_t*));
    if (!distribution) {
        fprintf(stderr, "memory allocation error\n");
    }

    for (size_t i = 0; i < number_positions; ++i) {
        distribution[i] = calloc(MAX_AGE - MIN_AGE, sizeof(size_t));
        if (!distribution[i]) {
            fprintf(stderr, "memory allocation error\n");
        }
    }

    //fprintf(stdout, "incorrect input type work\n");

    char *cur_position = (db->set_records)[0]->position;

    size_t count_pos = 0;
    for (size_t i = 0; i < number_records; ++i) {
        if (strcmp(cur_position, (db->set_records)[i]->position) == 0) {
            distribution[count_pos][(db->set_records)[i]->experience - MIN_AGE - 1] += (db->set_records)[i]->salary;
        } else {
            ++count_pos;

            cur_position = (db->set_records[i])->position;
        }
    }

    for (size_t i = 0; i < number_positions; ++i) {
        for (size_t j = 0; j < MAX_AGE - MIN_AGE; ++j) {
            //fprintf(stdout, "%zu ", distribution[i][j]);
        }
        //fprintf(stdout, "\n");
    }

    for (size_t i = 0; i < number_positions; ++i) {
        free(distribution[i]);
    }

    free(distribution);
}
