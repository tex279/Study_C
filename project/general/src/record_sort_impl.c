#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "load_database.h"

bool position_rule_less(const record_t *r_left, const record_t *r_right) {
    size_t length_l = strlen(r_left->position);
    size_t length_r = strlen(r_right->position);

    size_t length_compare = length_r;

    if (length_l < length_compare) {
        length_compare = length_l;
    }


    fprintf(stdout, "%s\n%s\n", r_left->position, r_right->position);
    fprintf(stdout, "%zu\n", length_compare);


    for (size_t i = 0; i < length_compare; ++i) {
        if ((r_left->position)[i] > (r_right->position)[i]) {
            return true;
        } else {
            if ((r_left->position)[i] == (r_right->position)[i]) {
                continue;
            }
        }

        if ((r_left->position)[i] < (r_right->position)[i]) {
            return false;
        }
    }

    return false;
}

void swap_record(record_t *r_left, record_t *r_right) {
    record_t tmp;

    assignment_record(&tmp, r_left);
    assignment_record(r_left, r_right);
    assignment_record(r_right, &tmp);
}

void sort_set_record(record_t **record, const size_t number_records, const sort_rule_t rule) {
    bool sorted = false;

    fprintf(stdout, "%c %c %c %c\n", (int)'C', (int)'o', (int)'o', (int)'k');
    fprintf(stdout, "%c %c %c %c\n", (int)'C', (int)'o', (int)'m', (int)'p');
    fprintf(stdout, "%d %d %d %d\n", (int)'C', (int)'o', (int)'o', (int)'k');
    fprintf(stdout, "%d %d %d %d\n", (int)'C', (int)'o', (int)'m', (int)'p');

    while (!sorted) {
        sorted = true;

        for (size_t i = 0; i < number_records - 1; ++i) {
            if (rule(record[i], record[i + 1])) {
                swap_record(record[i], record[i + 1]);

                sorted = false;
            }
        }

        print_set_record(NULL, record, number_records);
        fprintf(stdout, "\n");
    }
}
