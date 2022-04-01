#pragma once //  NOLINT

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char *name;
    char *surname;
    char *gender;
    char *age;
    char *salary;
    char *position;
    char *experience;
} format_t;

typedef struct {
    char *name;
    char *surname;
    char *position;
    bool gender;
    size_t age;
    size_t salary;
    size_t experience;
} record_t;

enum length_format {
    L_NAME = 32,
    L_SURNAME = 64,
    L_GENDER = 8,
    L_AGE = 4,
    L_SALARY = 16,
    L_POSITION = 64,
    L_EXPERIENCE = 4
};

#define SUM_LENGTH (L_NAME + L_SURNAME + L_GENDER + L_AGE + L_SALARY + L_POSITION + L_EXPERIENCE)

//  load_data_in_memory
int load_database(const char *source, record_t ***record, size_t *number_records);

//  format functional
format_t *create_set_format();

void free_set_format(format_t *format);

//  record functional
record_t **create_set_record(const size_t number_records);

int get_record(const char *source, record_t **out, const format_t *format);

void assignment_record(record_t *target, const record_t *source);

int print_record(FILE* target, const record_t *source);

int print_set_record(const char *path_output, record_t **source, const size_t number_records);

void free_set_record(record_t **record, const size_t number_records);

//  sort record
typedef bool (*sort_rule_t)(const record_t *r_left, const record_t *r_right);

bool position_rule_less(const record_t *r_left, const record_t *r_right);

void swap_record(record_t *r_left, record_t *r_right);

void sort_set_record(record_t **record, const size_t number_records, const sort_rule_t rule);

