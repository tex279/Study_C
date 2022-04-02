#pragma once //  NOLINT

#define ERR_ACOC -1
#define ERR_OPEN_FILE -2
#define ERR_CLOSE_FILE -3

#define SUCCESS 1

#include "load_database.h"

int get_average_salary_report(const char *target, const database_t *db);

size_t **get_distribution(FILE *target, const database_t *db);

void print_report_salary(FILE *target, size_t **distribution, const size_t number_pos, const size_t inter_exp);
