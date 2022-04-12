#pragma once //  NOLINT

#define ERR_ACOC -1
#define SUCCESS 1

#define ERR_OPEN_F_WRITE_M "error open file for write\n"
#define ERR_CLOSE_F_M "failed close file\n"

#define ERR_GET_REPORT_M "error get report\n"

#include "load_database.h"

int print_report_position(const char *target, const size_t *distribution);

int get_report_salary(record_t **begin, const size_t count_out_pos, const size_t end);

int get_average_salary_report(const database_t *db);
