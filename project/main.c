#include <stdio.h>
#include <stdlib.h>

#include "load_database.h"

#define NEEDED_COUNT_ARG 2

#define ERR_INPUT -1
#define ERR_WRONG_TYPE_WORK -2
#define ERR_LOAD_DATA -3

#define IMPERATIVE_MODEL 1
#define MULTI_THREADED_MODEL 2

#define SUCCESS 1

int main(int argc, const char **argv) {
    if (argc < NEEDED_COUNT_ARG) {
        fprintf(stderr, "incorrect input\n");
        return ERR_INPUT;
    }

    database_t *db = create_database();

    if (load_database(argv[2], db) < 0) {
        fprintf(stderr, "error load_data\n");
        return ERR_LOAD_DATA;
    }

    //sort_set_record(db->set_records, db->number_records, position_rule_less);

    sort_set_record_q(db->set_records, db->number_records, position_rule_less);

    char* end = NULL;
    long type_work = strtol(argv[1], &end, 0);
    if (*end != '\0') {
        fprintf(stdout, "incorrect input type work\n");
        return ERR_INPUT;
    }

    switch (type_work) {
        case IMPERATIVE_MODEL: {
            break;
        }
        case MULTI_THREADED_MODEL: {
            break;
        }
        default: {
            fprintf(stderr, "incorrect input type work: not such type");
            return ERR_WRONG_TYPE_WORK;
        }
    }

    print_set_record(argv[3], db->set_records, db->number_records);

    free_database(db);

    return SUCCESS;
}
