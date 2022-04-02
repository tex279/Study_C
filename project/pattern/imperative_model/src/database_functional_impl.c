#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "database_functional.h"
#include "matrix.h"

#define MAX_AGE 100
#define MIN_AGE 21

size_t **get_distribution(FILE *target, const database_t *db) {
    size_t number_records = db->number_records;

    size_t **distribution  = create_matrix(db->number_positions, MAX_AGE - MIN_AGE);
    if (!distribution) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    char *cur_position = (db->set_records)[0]->position;

    fprintf(target, "Position %s - %d\n", cur_position, 1);

    size_t count_pos = 0;
    for (size_t i = 0; i < number_records; ++i) {
        if (strcmp((db->set_records)[i]->position, cur_position) != 0) {
            ++count_pos;

            cur_position = (db->set_records[i])->position;

            fprintf(target, "Position %s - %zu\n", cur_position, count_pos + 1);
        }

        distribution[count_pos][(db->set_records)[i]->experience] += (db->set_records)[i]->salary;
    }

    return distribution;
}

void print_report_salary(FILE *target, size_t **distribution, const size_t number_pos, const size_t interval_exp) {
    fprintf(target, "Average salary report for:\n");

    for (size_t i = 0; i < number_pos; ++i) {
        for (size_t j = 0; j < interval_exp; ++j) {
            if (distribution[i][j]) {
                fprintf(target, "position - %zu ", i + 1);

                size_t exp = j;

                if (!j) {
                    exp = j + 1;
                }

                fprintf(target, "exp %zu - %zu ", j, distribution[i][j] /  exp);

                fprintf(target, "\n");
            }
        }
    }
}

int get_average_salary_report(const char *path_out, const database_t *db) {
    FILE *target = stdout;

    if (path_out) {
        target = fopen(path_out, "w+");
        if (!target) {
            fprintf(stderr, "error open file for write\n");
            return ERR_OPEN_FILE;
        }
    }

    size_t **distribution = get_distribution(target, db);
    if (!distribution) {
        return ERR_ACOC;
    }

    print_report_salary(target, distribution, db->number_positions, MAX_AGE - MIN_AGE);

    if (path_out) {
        if (fclose(target)) {
            fprintf(stderr, "failed close file\n");
            return ERR_CLOSE_FILE;
        }
    }

    free_matrix(distribution, db->number_positions);

    return SUCCESS;
}
