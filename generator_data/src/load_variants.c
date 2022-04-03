#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "load_variants.h"

#include "utils.h"

#define BUF_SIZE 64

#define LENGTH_STRING_FORMAT 10

int get_set(const char *source, char ***set_l) {
    FILE *flow_source = fopen(source, "r");
    if (!flow_source) {
        fprintf(stderr, "error open file for read\n");
        return ERR_OPEN_FILE;
    }

    int count = 0;
    fscanf(flow_source, "%d", &count);

    char **set = calloc((size_t)count, sizeof(char*));
    if (!set) {
        fprintf(stderr, "memory allocation error\n");
        return ERR_ACOC;
    }

    char *format = create_format(BUF_SIZE, LENGTH_STRING_FORMAT);
    if (!format) {
        return ERR_ACOC;
    }

    for (int i = 0; i < count; ++i) {
        char buf[BUF_SIZE];

        if (fscanf(flow_source, format, buf) != 1) {
            free(format);
            fprintf(stderr, "error read record\n");
            return ERR_READ;
        }

        set[i] = create_str(buf);
    }

    free(format);

    if (fclose(flow_source)) {
        fprintf(stderr, "failed close file\n");
        return ERR_CLOSE_FILE;
    }

    *set_l = set;

    return count;
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

    int count_variants = 0;

    count_variants = get_set(argv[++pos],  &db->set_female_name);
    if (count_variants < 0) {
        free(db);
        return NULL;
    }
    db->count_female_name = (size_t)count_variants;

    count_variants = get_set(argv[++pos], &db->set_male_name);
    if (count_variants < 0) {
        free_database(db);
        return NULL;
    }
    db->count_male_name = (size_t)count_variants;

    count_variants= get_set(argv[++pos], &db->set_surname);
    if (count_variants < 0) {
        free_database(db);
        return NULL;
    }
    db->count_surname = (size_t)count_variants;

    count_variants = get_set(argv[++pos], &db->set_female_surname);
    if (count_variants < 0) {
        free_database(db);
        return NULL;
    }
    db->count_female_surname = (size_t)count_variants;

    count_variants = get_set(argv[++pos], &db->set_male_surname );
    if (count_variants < 0) {
        free_database(db);
        return NULL;
    }
    db->count_male_surname = (size_t)count_variants;

    count_variants = get_set(argv[++pos], &db->set_position);
    if (count_variants < 0) {
        free_database(db);
        return NULL;
    }
    db->count_position = (size_t)count_variants;

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

