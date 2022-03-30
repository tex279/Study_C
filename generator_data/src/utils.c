#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

#define BUF_SIZE 64

#define LENGTH_STRING_FORMAT 10

char *create_str(const char *source) {
    size_t len = strlen(source);

    char *tmp = calloc(len + 1, sizeof(char));
    if (!tmp) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    tmp = strncpy(tmp, source, len);

    tmp[len] = '\0';

    return tmp;
}

char *create_format(const size_t size_str, const size_t size_format) {
    char *format = calloc(size_format + 1, sizeof(char));
    if (!format) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    snprintf(format, size_format + 1, "%%%zus", size_str);

    return format;
}

char **get_set(const char *source) {
    FILE *flow_source = fopen(source, "r");
    if (!flow_source) {
        fprintf(stderr, "error open file for read");
        return NULL;
    }

    size_t count = 0;
    fscanf(flow_source, "%zu", &count);

    char **set = calloc(count, sizeof(char*));
    if (!set) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    char *format = create_format(BUF_SIZE, LENGTH_STRING_FORMAT);
    if (!format) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        char buf[BUF_SIZE];

        if (fscanf(flow_source, format, buf) != 1) {
            free(format);
            return NULL;
        }

        set[i] = create_str(buf);
    }

    free(format);

    if (fclose(flow_source)) {
        fprintf(stderr, "failed close file");
        return NULL;
    }

    return set;
}

database_t *create_db() {
    database_t *db = calloc(1, sizeof(database_t));
    if (!db) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    return db;
}

database_t *load_data(const char **argv, size_t pos) {
    database_t *db = create_db();
    if (!db) {
        return NULL;
    }

    db->set_female_name = get_set(argv[++pos]);
    if (!db->set_female_name) {
        free(db);
        return NULL;
    }

    db->set_male_name = get_set(argv[++pos]);
    if (!db->set_male_name) {
        free(db);
        free_set(db->set_female_name);
        return NULL;
    }

    db->set_surname = get_set(argv[++pos]);
    if (!db->set_surname) {
        free(db);
        free_set(db->set_female_name);
        free_set(db->set_male_name);
        return NULL;
    }

    db->set_female_surname = get_set(argv[++pos]);
    if (!db->set_female_surname) {
        free(db);
        free_set(db->set_female_name);
        free_set(db->set_male_name);
        free_set(db->set_surname);
        return NULL;
    }

    db->set_male_surname = get_set(argv[++pos]);
    if (!db->set_male_surname) {
        free(db);
        free_set(db->set_female_name);
        free_set(db->set_male_name);
        free_set(db->set_surname);
        free_set(db->set_male_surname);
        return NULL;
    }

    db->set_position = get_set(argv[++pos]);
    if (!db->set_position) {
        free(db);
        free_set(db->set_female_name);
        free_set(db->set_male_name);
        free_set(db->set_surname);
        free_set(db->set_male_surname);
        free_set(db->set_position);
        return NULL;
    }

    return db;
}

void free_set(char **set) {
    for (size_t i = 0; i < sizeof(set) + 1; ++i) {
        free(set[i]);
    }

    free(set);
}

void free_database(database_t *db) {
    free_set(db->set_female_name);
    free_set(db->set_male_name);
    free_set(db->set_surname);
    free_set(db->set_female_surname);
    free_set(db->set_male_surname);
    free_set(db->set_position);

    free(db);
}