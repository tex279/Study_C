#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "load_database.h"
#include "utils.h"

#define ERR_CREATE_SET_FORMATS -5
#define ERR_GET_NUMBER_RECORDS -6
#define ERR_CREATE_SET_RECORDS -7
#define ERR_GET_RECORD -8

#define ERR_OPEN_FILE -1
#define ERR_CREATE_FILE -2
#define ERR_WRITE_FILE -3
#define ERR_CLOSE_FILE -4

int input(const char *source, record_t ***record, size_t *number_records) {
    format_t *set_format = create_set_format();
    if (!set_format) {
        fprintf(stderr, "error create set formats\n");
        return ERR_CREATE_SET_FORMATS;
    }

    FILE *target = fopen(source, "r");
    if (!target) {
        free_set_format(set_format);
        fprintf(stdout, "error open file for read\n");
        return ERR_OPEN_FILE;
    }

    const size_t numb_records;
    if (fscanf(target, "%zu\n", &numb_records) != 1) {
        fprintf(stdout, "error get number records\n");

        free_set_format(set_format);
        fclose(target);

        return ERR_GET_NUMBER_RECORDS;
    }

    record_t **set_record = create_set_record(numb_records);
    if (!set_record) {
        fprintf(stdout, "error create set records\n");

        free_set_format(set_format);
        fclose(target);

        return ERR_CREATE_SET_RECORDS;
    }


    fprintf(stdout, "%zu\n", numb_records);


    for (size_t i = 0; i < numb_records; ++i) {
        char global[SUM_LENGTH + 1];

        fgets(global, sizeof(global), target);


        record_t *tmp = NULL;
        if (get_record(global, &tmp, set_format) < 0) {
            fprintf(stderr, "error get records\n");

            fclose(target);
            free_set_format(set_format);
            free_set_record(set_record, i);
            return ERR_GET_RECORD;
        }

        assignment_record(set_record[i], tmp);

        free(tmp);
    }

    *record = set_record;
    *number_records = numb_records;

    free_set_format(set_format);

    if (fclose(target)) {
        fprintf(stderr, "failed close file\n");
        return ERR_CLOSE_FILE;
    }

    return SUCCESS;
}
