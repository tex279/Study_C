#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "database_functional_multu_thread.h"

#include "matrix.h"

#define MAX_AGE 100
#define MIN_AGE 18

#define BUF_STR_PATH 62

const char add_to_path_dur[] = {"report/"};
const char format_res[] = {".txt"};

#define AGE_INTERVAL 82

#define ERR_OPEN_FILE -2
#define ERR_CLOSE_FILE -3
#define ERR_GET_REPORT -4
#define ERR_CREATE_THREAD -5


size_t *get_count_workers_ml(const database_t *db) {
    size_t number_records = db->number_records;

    size_t *distribution  = calloc(db->number_positions, sizeof(size_t));
    if (!distribution) {
        fprintf(stderr, "memory allocation error for workers\n");
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
        fprintf(stderr, "error open file for write for position\n");
        return ERR_OPEN_FILE;
    }

    for (size_t i = 0; i < AGE_INTERVAL; ++i) {
        if (distribution[i]) {
            fprintf(tg, "exp %zu - %zu\n", i, distribution[i] /  i);
        }
    }

    if (fclose(tg)) {
        fprintf(stderr, "failed close file for position\n");
        return ERR_CLOSE_FILE;
    }

    return SUCCESS;
}

int get_report_salary_ml(record_t **begin, const size_t end, size_t **sum_salary) {
    char *cur_position = (begin[0])->position;

    char path_out[BUF_STR_PATH];

    size_t i = 0;
    size_t k = 0;
    while (k < end) {
        //  fprintf(stdout, "%s\n", (begin)[0]->position);

        if (strcmp((begin)[k]->position, cur_position) == 0) {
            sum_salary[i][(begin)[k]->experience] += (begin)[k]->salary;

            ++k;
        } else {
            snprintf(path_out, BUF_STR_PATH, "%s%s%s", add_to_path_dur, cur_position, format_res);

            print_report_position_ml(path_out, sum_salary[i]);

            cur_position = (begin[k])->position;

            ++i;
        }
    }

    snprintf(path_out, BUF_STR_PATH, "%s%s%s", add_to_path_dur, cur_position, format_res);

    print_report_position_ml(path_out, sum_salary[i]);

    return SUCCESS;
}

void *get_interval_report_pos(void *ptr) {
    report_thr_args *args = (report_thr_args *)ptr;

    if (get_report_salary_ml(args->begin, args->end, args->sum_salary) < 0) {
        fprintf(stderr, "error get report\n");
        return NULL;
    }

    fprintf(stdout,"HELLO\n");

    free_matrix(args->sum_salary, args->count_pos);

    free(args);

    if (pthread_detach(pthread_self())) {
        fprintf(stderr, "error detach\n");
        return NULL;
    }

    return NULL;
}

/*size_t shift_pos(const size_t step, const size_t begin, const size_t iter, const size_t *set) {
    size_t res = begin;

    for (size_t i = 0; i < step; ++i) {
        res += set[iter + i];
    }

    return res;
}*/

int get_average_salary_report_ml(const database_t *db) {
    size_t *count_workers = get_count_workers_ml(db);
    if (!count_workers) {
        return ERR_ACOC;
    }

    //  size_t numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    //  fprintf(stdout, "%zu\n", numCPU);

    for (size_t i = 0; i < db->number_positions; ++i) {
        fprintf(stdout, "%zu ", count_workers[i]);
    }
    fprintf(stdout, "\n");

    size_t cur_begin = 0;
    for (size_t i = 0; i < db->number_positions; ++i) {
        report_thr_args *arg = (report_thr_args *)malloc(sizeof(report_thr_args));

        fprintf(stdout, "%zu %zu\n", cur_begin, count_workers[i]);

        arg->begin = &((db->set_records)[cur_begin]);
        arg->count_pos = 1;
        arg->end = count_workers[i];

        arg->sum_salary = create_matrix(arg->count_pos, AGE_INTERVAL);
        if (!arg->sum_salary) {
            return ERR_ACOC;
        }

        pthread_t thr;

        if (pthread_create(&thr, NULL, get_interval_report_pos, (void *)arg)) {
            fprintf(stderr, "create thread\n");
            return ERR_CREATE_THREAD;
        }

        cur_begin += count_workers[i];
    }

    free(count_workers);

    return SUCCESS;
}
