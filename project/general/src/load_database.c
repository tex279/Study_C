#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "load_database.h"
#include "utils.h"

#define ERR_CREATE_SET_FORMATS -5
#define ERR_GET_NUMBERS -6
#define ERR_CREATE_SET_RECORDS -7
#define ERR_GET_RECORD -8

database_t *create_database() {
    database_t *db = calloc(1, sizeof(database_t*));
    if (!db) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    return db;
}

int load_database(const char *source, database_t *db) {
    format_t *set_format = create_set_format();
    if (!set_format) {
        fprintf(stderr, "error create set formats\n");
        return ERR_CREATE_SET_FORMATS;
    }

    FILE *target = fopen(source, "r");
    if (!target) {
        free_set_format(set_format);
        fprintf(stderr, "error open file for read\n");
        return ERR_OPEN_FILE;
    }

    if (fscanf(target, "%zu%zu\n", &(db->number_records),  &(db->number_positions)) != 2) {
        fprintf(stderr, "error get number records and number positions\n");

        free_set_format(set_format);
        fclose(target);

        return ERR_GET_NUMBERS;
    }

    size_t numb_records = db->number_records;

    db->set_records = create_set_record(numb_records);
    if (!db->set_records) {
        fprintf(stderr, "error create set records\n");

        free_set_format(set_format);
        fclose(target);

        return ERR_CREATE_SET_RECORDS;
    }

    char global[SUM_LENGTH + 1];
    int length_buf = sizeof(global);
    for (size_t i = 0; i < numb_records; ++i) {

        fgets(global, length_buf, target);

        record_t *tmp = NULL;
        if (get_record(global, &tmp, set_format) < 0) {
            fprintf(stderr, "error get records\n");

            fclose(target);
            free_set_format(set_format);
            free_set_record(db->set_records, i);
            return ERR_GET_RECORD;
        }

        assignment_record(db->set_records[i], tmp);

        free(tmp);
    }

    free_set_format(set_format);

    if (fclose(target)) {
        fprintf(stderr, "failed close file\n");
        return ERR_CLOSE_FILE;
    }

    return SUCCESS;
}

void free_database(database_t *db) {
    free_set_record(db->set_records, db->number_records);

    free(db);
}