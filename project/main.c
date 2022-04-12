#include <stdio.h>
#include <stdlib.h>

#include "database_functional.h"

#include "database_functional_multu_thread.h"

#define NEEDED_COUNT_ARG 3

#define ERR_INPUT -1
#define ERR_WRONG_TYPE_WORK -2
#define ERR_LOAD_DATA -3
#define ERR_GET_REPORT -4

#define NEEDED_SORT 1
#define DONT_NEEDED_SORT 2

#define IMPERATIVE_MODEL 1
#define MULTI_THREADED_MODEL 2

int get_report(database_t *db, long type_work) {
    switch (type_work) {
        case IMPERATIVE_MODEL: {
            if (get_average_salary_report(db) < 0) {
                fprintf(stderr, "error get average salary report\n");
                free_database(db);
                return ERR_GET_REPORT;
            }

            break;
        }
        case MULTI_THREADED_MODEL: {
            if (get_average_salary_report_ml(db) < 0) {
                fprintf(stderr, "error get average salary report\n");
                free_database(db);
                return ERR_GET_REPORT;
            }

            break;
        }
        default: {
            fprintf(stderr, "incorrect input type work: not such type");
            return ERR_WRONG_TYPE_WORK;
        }
    }

    return EXIT_SUCCESS;
}

int main(int argc, const char **argv) {
    if (argc < NEEDED_COUNT_ARG) {
        fprintf(stderr, "incorrect input\n");
        return ERR_INPUT;
    }

    char* end = NULL;
    long sort = strtol(argv[1], &end, 0);
    if (*end != '\0') {
        fprintf(stderr, "incorrect input type work\n");
        return ERR_INPUT;
    }

    const char *path_to_db = argv[2];

    database_t *db = create_database();

    if (load_database(path_to_db, db) < 0) {
        fprintf(stderr, "error load_data\n");
        return ERR_LOAD_DATA;
    }

    if (sort == NEEDED_SORT) {
        sort_quick_recursive(db->set_records, db->number_records, position_rule_less);

        const char *path_to_sorted = argv[3];

        print_set_record(path_to_sorted, db);
    }

    long type_work = strtol(argv[4], &end, 0);
    if (*end != '\0') {
        fprintf(stderr, "incorrect input type work\n");
        return ERR_INPUT;
    }

    if (get_report(db, type_work) < 0) {
        return ERR_GET_REPORT;
    }

    free_database(db);

    return EXIT_SUCCESS;
}
