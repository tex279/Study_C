#pragma once //  NOLINT

#define ERR_ACOC -1
#define SUCCESS 1

#define ERR_OPEN_F_READ_M "error open file for read\n"
#define ERR_OPEN_F_WRITE_M "error open file for write\n"
#define ERR_CLOSE_F_M "failed close file\n"

#define ERR_GET_REPORT_M "error get report\n"

#define ERR_ALOC_M "memory allocation error\n"

#include "load_database.h"

size_t *get_count_workers_ml(const database_t *db);

int print_report_position_ml(const char *target, const size_t *distribution);

int get_report_salary_ml(record_t **begin, const size_t end, const size_t count_pos);

typedef struct {
    record_t **begin;
    size_t end;
    size_t count_pos;
} report_thr_args;

void *get_interval_report_pos(void *ptr);

int get_average_salary_report_ml(const database_t *db);

