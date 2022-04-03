#pragma once //  NOLINT

#define ERR_ACOC -1

#define SUCCESS 1

#include "load_database.h"

size_t *get_count_workers(const database_t *db);

int print_report_position(const char *target, const size_t *distribution);

int get_report_salary(record_t **begin, const size_t count_out);

int get_average_salary_report_ml(const database_t *db);

