#pragma once //  NOLINT

#define ERR_ACOC -1

#define ERR_OPEN_FILE -1
#define ERR_CLOSE_FILE -2
#define ERR_READ -3


typedef struct {
    char **set_female_name;
    size_t count_female_name;

    char **set_male_name;
    size_t count_male_name;

    char **set_surname;
    size_t count_surname;

    char **set_female_surname;
    size_t count_female_surname;

    char **set_male_surname;
    size_t count_male_surname;

    char **set_position;
    size_t count_position;
} database_t;

//  create database variants
int get_set(const char *source, char ***set_l);

database_t *load_data(const char **argv, size_t pos);

void free_set(char **set);

void free_database(database_t *db);
