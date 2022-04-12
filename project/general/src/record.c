#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "load_database.h"
#include "utils.h"

#define ERR_GET_FIELD -1
#define ERR_CONVERT_NUMBER -2

#define MAX_BUF_LENGTH 64

const char female[] = {"female"};

#define GET_FIELD_STR(field_name, source, indent, format, buf, target) do {     \
    if (sscanf(&source[indent], format, buf) != 1) {                            \
        fprintf(stderr, "%s - %s", field_name, ERR_READ_FIELD_M);               \
        free(record);                                                           \
        return ERR_GET_FIELD;                                                   \
    }                                                                           \
                                                                                \
    target = create_str(buf);                                                   \
    if (!target) {                                                              \
        return ERR_ALOCC;                                                       \
    }                                                                           \
                                                                                \
    indent += strlen(buf) + 1;                                                  \
} while (0)

#define GET_FIELD_NUMBER(field_name, source, indent, format, buf, target) do {  \
    if (sscanf(&source[indent], format, buf) != 1) {                            \
        fprintf(stderr, "%s - %s", field_name, ERR_READ_FIELD_M);               \
        return ERR_GET_FIELD;                                                   \
    }                                                                           \
                                                                                \
    target = strtoul(buf, &end, 0);                            \
    if (*end != '\0') {                                                         \
        fprintf(stderr, "%s - %s", field_name, ERR_CONVERSION_M);               \
        return ERR_CONVERT_NUMBER;                                              \
    }                                                                           \
                                                                                \
    indent += strlen(buf) + 1;                                                  \
} while (0)

record_t *create_record() {
    record_t *record = calloc(1, sizeof(record_t));
    if (!record) {
        fprintf(stderr, ERR_ALOC_M);

        free(record);
        return NULL;
    }

    return record;
}

record_t **create_set_record(const size_t number_records) {
    record_t **set_record = calloc(number_records, sizeof(record_t*));
    if (!set_record) {
        fprintf(stderr, ERR_ALOC_M);
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

    char buf[MAX_BUF_LENGTH];

    GET_FIELD_STR("name", source, indent, format->name, buf, record->name);

    GET_FIELD_STR("surname", source, indent, format->surname, buf, record->surname);

    if (sscanf(&source[indent], format->gender, buf) != 1) {
        fprintf(stderr, "%s %s", "gender -", ERR_READ_FIELD_M);
        return ERR_GET_FIELD;
    }
    if (strcmp(buf, female) == 0) {
        record->gender = true;
    } else {
        record->gender = false;
    }

    indent += strlen(buf) + 1;

    GET_FIELD_NUMBER("age", source, indent, format->age, buf, record->age);

    GET_FIELD_NUMBER("salary", source, indent, format->salary, buf, record->salary);

    GET_FIELD_STR("position", source, indent, format->position, buf, record->position);

    GET_FIELD_NUMBER("experience", source, indent, format->experience, buf, record->experience);

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
            fprintf(stderr, ERR_OPEN_F_READ_M);
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
            fprintf(stderr, ERR_CLOSE_F_M);
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

