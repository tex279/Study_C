#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "load_database.h"
#include "utils.h"

#define ERR_GET_FIELD -1
#define ERR_CONVERT_NUMBER -2

const char female[] = {"female"};

record_t *create_record() {
    record_t *record = calloc(1, sizeof(record_t));
    if (!record) {
        fprintf(stderr, "memory allocation error\n");

        free(record);
        return NULL;
    }

    return record;
}

record_t **create_set_record(const size_t number_records) {
    record_t **set_record = calloc(number_records, sizeof(record_t*));
    if (!set_record) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    for (size_t i = 0; i < number_records; ++i) {
        set_record[i] = create_record();
        if (!set_record[i]) {
            free(set_record);
            return NULL;
        }
    }

    return set_record;
}


int get_record(const char *source, record_t *record, const format_t *format) {
    size_t indent = 0;

    char *end = NULL;

    char buf_name[L_NAME];
    if (sscanf(&source[indent], format->name, buf_name) != 1) {
        fprintf(stderr, "error get field name\n");
        free(record);
        return ERR_GET_FIELD;
    }
    record->name = create_str(buf_name);
    if (!record->name) {
        return ERR_ALOCC;
    }

    indent += strlen(buf_name) + 1;

    char buf_surname[L_SURNAME];
    if (sscanf(&source[indent], format->surname, buf_surname) != 1) {
        fprintf(stderr, "error get field surname\n");
        return ERR_GET_FIELD;
    }
    record->surname = create_str(buf_surname);
    if (!record->surname) {
        return ERR_ALOCC;
    }

    indent += strlen(buf_surname) + 1;


    char buf_gender[L_GENDER];
    if (sscanf(&source[indent], format->position, buf_gender) != 1) {
        fprintf(stderr, "error get field gender\n");
        return ERR_GET_FIELD;
    }
    if (strcmp(buf_gender, female) == 0) {
        record->gender = true;
    } else {
        record->gender = false;
    }

    indent += strlen(buf_gender) + 1;


    char buf_age[L_AGE];
    if (sscanf(&source[indent], format->age, buf_age) != 1) {
        fprintf(stderr, "error get field age\n");
        return ERR_GET_FIELD;
    }

    record->age = strtoul(buf_age, &end, 0);
    if (*end != '\0') {
        fprintf(stderr, "error convert str to number age\n");
        return ERR_CONVERT_NUMBER;
    }

    indent += strlen(buf_age) + 1;


    char buf_salary[L_SALARY];
    if (sscanf(&source[indent], format->salary, buf_salary) != 1) {
        fprintf(stderr, "error get field salary\n");
        return ERR_GET_FIELD;
    }

    record->salary = strtoul(buf_salary, &end, 0);
    if (*end != '\0') {
        fprintf(stderr, "error convert str to number salary\n");
        return ERR_CONVERT_NUMBER;
    }
    indent += strlen(buf_salary) + 1;


    char buf_position[L_POSITION];
    if (sscanf(&source[indent], format->position, buf_position) != 1) {
        fprintf(stderr, "error get field position\n");
        return ERR_GET_FIELD;
    }
    record->position = create_str(buf_position);
    if (!record->position) {
        return ERR_ALOCC;
    }

    indent += strlen(buf_position);


    char buf_experience[L_EXPERIENCE];
    if (sscanf(&source[indent], format->experience, buf_experience) != 1) {
        fprintf(stderr, "error get field experience\n");
        return ERR_GET_FIELD;
    }

    record->experience = strtoul(buf_experience, &end, 0);
    if (*end != '\0') {
        fprintf(stderr, "error convert str to number experience\n");
        return ERR_CONVERT_NUMBER;
    }

    return SUCCESS;
}

int print_record(FILE* target, const record_t *source) {
    fprintf(target, "%s ", source->name);

    fprintf(target, "%s ", source->surname);

    //  gender
    if (source->gender) {
        fprintf(target, "%s ", "female");
    } else {
        fprintf(target, "%s ", "male");
    }

    //  age
    fprintf(target, "%zu ", source->age);

    //  salary
    fprintf(target, "%zu ", source->salary);

    //  position(job)
    fprintf(target, "%s ", source->position);

    //  experience
    fprintf(target, "%zu\n",  source->experience);

    return SUCCESS;
}

int print_set_record(const char *path_output, const database_t *db) {
    FILE *target = stdout;

    if (path_output) {
        target = fopen(path_output, "w+");
        if (!target) {
            fprintf(stderr, "error open file for read\n");
            return ERR_OPEN_FILE;
        }
    }

    size_t number_records = db->number_records;

    fprintf(target, "%zu\n", number_records);
    fprintf(target, "%zu\n", db->number_positions);

    for (size_t i = 0; i < number_records; ++i) {
        print_record(target, db->set_records[i]);
    }

    if (path_output) {
        if (fclose(target)) {
            fprintf(stderr, "failed close file\n");
            return ERR_CLOSE_FILE;
        }
    }

    return SUCCESS;
}

int free_record(record_t *record) {
    free(record->name);
    free(record->surname);
    free(record->position);
    free(record);

    return SUCCESS;
}

int free_set_record(record_t **record, const size_t number_records) {
    for (size_t i = 0; i < number_records; ++i) {
        free_record(record[i]);
    }

    free(record);

    return SUCCESS;
}

