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
    record_t tmp = *r_left;
    *r_left = *r_right;
    *r_right = tmp;
}

int sort_set_record(record_t **record, const size_t number_records, const sort_rule_t rule) {
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

    return SUCCESS;
}
