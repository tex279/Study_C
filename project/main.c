#include <stdio.h>
#include <stdlib.h>

#include "load_database.h"
#include "database_functional.h"

#define NEEDED_COUNT_ARG 2

#define ERR_INPUT -1
#define ERR_WRONG_TYPE_WORK -2
#define ERR_LOAD_DATA -3
#define ERR_GET_REPORT -4

#define IMPERATIVE_MODEL 1
#define MULTI_THREADED_MODEL 2

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

    sort_set_record(db->set_records, db->number_records, position_rule_less);

    print_set_record(argv[3], db->set_records, db->number_records);

    char* end = NULL;
    long type_work = strtol(argv[1], &end, 0);
    if (*end != '\0') {
        fprintf(stderr, "incorrect input type work\n");
        return ERR_INPUT;
    }

    switch (type_work) {
        case IMPERATIVE_MODEL: {
            if (get_average_salary_report(argv[4], db) < 0) {
                fprintf(stderr, "error get average salary report\n");
                free_database(db);
                return ERR_GET_REPORT;
            }

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

    free_database(db);

    return EXIT_SUCCESS;
}
