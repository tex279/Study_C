#pragma once //  NOLINT

#define ERR_ACOC -1

#define SUCCESS 1

#include "load_database.h"

size_t *get_count_workers_ml(const database_t *db);

int print_report_position_ml(const char *target, const size_t *distribution);

int get_report_salary_ml(record_t **begin, const size_t count_out_pos, const size_t end);

typedef struct {
    record_t **begin;
    size_t end;
    size_t count_pos;
} report_thr_args;

void *get_interval_report_pos(void *ptr);

//size_t shift_pos(const size_t step, const size_t begin, const size_t iter, const size_t *set);

int get_average_salary_report_ml(const database_t *db);

