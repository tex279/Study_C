#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "database_functional.h"

#include "matrix.h"

#define MAX_AGE 100
#define MIN_AGE 18

const char add_to_path[] = {"report/"};
const char format[] = {".txt"};

#define BUF_STR_PATH 32

#define AGE_INTERVAL 82

#define ERR_OPEN_FILE -2
#define ERR_CLOSE_FILE -3
#define ERR_GET_REPORT -4

int print_report_position(const char *target, const size_t *distribution) {
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

int get_report_salary(record_t **begin, const size_t count_out_pos, const size_t end) {
    size_t **sum_salary = create_matrix(count_out_pos, AGE_INTERVAL);
    if (!sum_salary) {
        return ERR_ACOC;
    }

    char *cur_position = (begin[0])->position;

    fprintf(stdout, "%zu %zu\n", count_out_pos, end);

    char path_out[BUF_STR_PATH];

    size_t i = 0;
    size_t k = 0;
    while (k < end) {
        if (strcmp((begin)[k]->position, cur_position) == 0) {
            sum_salary[i][(begin)[k]->experience] += (begin)[k]->salary;

            ++k;
        } else {
            snprintf(path_out, sizeof path_out, "%s%s%s", add_to_path, cur_position, format);

            print_report_position(path_out, sum_salary[i]);

            cur_position = (begin[k])->position;

            ++i;
        }
    }

    snprintf(path_out, sizeof path_out, "%s%s%s", add_to_path, cur_position, format);

    print_report_position(path_out, sum_salary[i]);

    free_matrix(sum_salary, count_out_pos);

    return SUCCESS;
}

int get_average_salary_report(const database_t *db) {
    if (get_report_salary(db->set_records, db->number_positions , db->number_records) < 0) {
        fprintf(stderr, "error get report\n");
        return ERR_GET_REPORT;
    }

    return SUCCESS;
}
