#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "database.h"

bool position_rule_less(const record_t *r_left, const record_t *r_right) {
    size_t length_l = strlen(r_left->position);
    size_t length_r = strlen(r_right->position);

    size_t length_compare = length_r;

    if (length_l < length_compare) {
        length_compare = length_l;
    }

    for (size_t i = 0; i < length_compare; ++i) {
        if ((r_left->position)[i] > (r_right->position)[i]) {
            return true;
        }

        break;
    }

    return false;
}

void swap_record(record_t *r_left, record_t *r_right) {
    record_t *tmp = *create_set_record(1);

    assignment_record(tmp, r_left);
    assignment_record(r_left, r_right);
    assignment_record(r_right, tmp);

    free(tmp);
}

void sort_set_record(record_t **record, const size_t number_records, const sort_rule_t rule) {
    bool sorted = false;

    while (!sorted) {
        sorted = true;

        for (size_t i = 0; i < number_records - 1; ++i) {
            if (rule(record[i], record[i + 1])) {
                swap_record(record[i], record[i + 1]);

                sorted = false;
            }
        }
    }
}