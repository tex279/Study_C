#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "database_functional_multu_thread.h"

#include "matrix.h"

#define MAX_AGE 100
#define MIN_AGE 18

char add_to_path[] = {"report/"};

#define BUF_STR_PATH 32

#define AGE_INTERVAL 82

#define ERR_OPEN_FILE -2
#define ERR_CLOSE_FILE -3
#define ERR_GET_REPORT -4


size_t *get_count_workers(const database_t *db) {
    size_t number_records = db->number_records;

    size_t *distribution  = calloc(db->number_positions, sizeof(size_t));
    if (!distribution) {
        fprintf(stdout, "memory allocation error\n");
        return NULL;
    }

    char *cur_position = (db->set_records)[0]->position;

    size_t count_pos = 0;
    for (size_t i = 0; i < number_records; ++i) {
        if (strcmp((db->set_records)[i]->position, cur_position) != 0) {
            ++count_pos;

            cur_position = (db->set_records[i])->position;
        }

        ++distribution[count_pos];
    }

    return distribution;
}

int print_report_position_ml(const char *target, const size_t *distribution) {
    FILE *tg = fopen(target, "w+");
    if (!tg) {
        fprintf(stderr, "error open file for write\n");
        return ERR_OPEN_FILE;
    }

    for (size_t i = 0; i < AGE_INTERVAL; ++i) {
        if (distribution[i]) {
            fprintf(tg, "exp %zu - %zu\n", i, distribution[i] /  i);
        }
    }

    if (fclose(tg)) {
        fprintf(stderr, "failed close file\n");
        return ERR_CLOSE_FILE;
    }

    return SUCCESS;
}

int get_report_salary_ml(record_t **begin, const size_t count_out) {
    size_t **sum_salary = create_matrix(count_out, AGE_INTERVAL);
    if (!sum_salary) {
        return ERR_ACOC;
    }

    char *cur_position = (begin[0])->position;

    size_t i = 1;
    size_t k = 0;
    while (i < count_out) {
        while (strcmp((begin)[k]->position, cur_position) == 0) {
            sum_salary[i][(begin)[k]->experience] += (begin)[k]->salary;

            ++k;
        }

        char path_out[BUF_STR_PATH];

        snprintf(path_out, sizeof path_out, "%s%s", add_to_path, cur_position);

        print_report_position_ml(path_out, sum_salary[i]);

        cur_position = (begin[k])->position;

        ++i;
    }

    free_matrix(sum_salary, count_out);

    return SUCCESS;
}

int get_average_salary_report_ml(const database_t *db) {
    size_t *count_workers = get_count_workers(db);
    if (!count_workers) {
        return ERR_ACOC;
    }

    if (get_report_salary_ml(db->set_records, db->number_positions) < 0) {
        fprintf(stderr, "error get report\n");
        return ERR_GET_REPORT;
    }

    free(count_workers);

    return SUCCESS;
}
