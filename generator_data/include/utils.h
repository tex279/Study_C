#pragma once //  NOLINT

#define SUCCESS 0

typedef struct {
    char **set_female_name;
    char **set_male_name;
    char **set_surname;
    char **set_female_surname;
    char **set_male_surname;
    char **set_position;
} database_t;

//  base
char *create_str(const char *source);

char *create_format(const size_t size_str, const size_t size_format);

char **get_set(const char *source);

database_t *load_data(const char **argv, size_t pos);

void free_set(char **set);

void free_database(database_t *db);
