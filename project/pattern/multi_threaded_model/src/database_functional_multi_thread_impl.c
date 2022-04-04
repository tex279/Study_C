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

const char add_to_path_dur[] = {"report_multi/"};
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

int get_report_salary_ml(record_t **begin, const size_t end, const  size_t count_pos) {
    size_t **sum_salary = create_matrix(count_pos, AGE_INTERVAL);
    if (!sum_salary) {
        return ERR_ACOC;
    }

    char *cur_position = (begin[0])->position;

    char path_out[BUF_STR_PATH];

    size_t i = 0;
    size_t k = 0;
    while (k < end) {
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

    free_matrix(sum_salary, count_pos);

    return SUCCESS;
}

void *get_interval_report_pos(void *ptr) {
    report_thr_args *args = (report_thr_args *)ptr;

    if (get_report_salary_ml(args->begin, args->end, args->count_pos) < 0) {
        fprintf(stdout, "error get report\n");
        return NULL;
    }

    free(args);

    return NULL;
}

size_t shift_pos(const size_t step, const size_t iter, const size_t *set) {
    size_t res = 0;

    for (size_t i = 0; i < step; ++i) {
        res += set[iter + i];
    }

    return res;
}

size_t *get_dynamic_distribution(const size_t res_count, const size_t count_objects, const size_t count_workers) {
    size_t *distribution  = calloc(res_count, sizeof(size_t));
    if (!distribution) {
        fprintf(stderr, "memory allocation error for get count workers thread\n");
        return NULL;
    }

    size_t min_count = count_objects / count_workers;
    size_t add = count_objects % count_workers;

    for (size_t i = 0; i < res_count; ++i) {
        if (add) {
            distribution[i] = min_count + 1;

            --add;
        } else {
            distribution[i] = min_count;
        }
    }

    return distribution;
}

int get_average_salary_report_ml(const database_t *db) {
    size_t *count_workers = get_count_workers_ml(db);
    if (!count_workers) {
        return ERR_ACOC;
    }

    size_t numCPU = sysconf(_SC_NPROCESSORS_ONLN);

    size_t partition = db->number_positions;
    if (partition > numCPU) {
        partition = numCPU;
    }

    size_t *distribution = get_dynamic_distribution(partition, db->number_positions, numCPU);
    if (!distribution) {
        return ERR_ACOC;
    }
    pthread_t thr[partition];

    size_t cur_begin = 0;
    size_t cur_pos = 0;
    for (size_t i = 0; i < partition; ++i) {
        report_thr_args *arg = (report_thr_args *)malloc(sizeof(report_thr_args));

        arg->begin = &((db->set_records)[cur_begin]);
        arg->count_pos = distribution[i];
        arg->end = shift_pos(distribution[i], cur_pos, count_workers);

        if (pthread_create(&thr[i], NULL, get_interval_report_pos, (void *)arg)) {
            fprintf(stderr, "create thread\n");
            return ERR_CREATE_THREAD;
        }
        cur_begin += shift_pos(distribution[i], cur_pos, count_workers);

        cur_pos += distribution[i];

    }

    for (size_t i = 0; i < partition; i++) {
        pthread_join(thr[i], NULL);
    }

    free(distribution);

    free(count_workers);

    return SUCCESS;
}
