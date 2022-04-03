#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "load_database.h"

bool position_rule_less(const record_t *r_left, const record_t *r_right) {
    if (strcmp(r_left->position, r_right->position) > 0) {
        return true;
    }

    return false;
}

void swap_record(record_t *r_left, record_t *r_right) {
    record_t tmp = *r_left;
    *r_left = *r_right;
    *r_right = tmp;
}

void sort_set_record_q(record_t **array, size_t l, size_t r, sort_rule_t rule) {
    size_t i = l;
    size_t j = r;

    record_t *pp_left = array[l];
    record_t *pp_right = array[r];
    record_t *pp_mid = array[(l + r) >> 1];

    if (rule(pp_left, pp_right)) {
        swap_record(pp_left, pp_right);
    }

    if (rule(pp_left, pp_mid)) {
        swap_record(pp_right, pp_mid);
    }

    record_t *p = pp_right;

    while (i <= j) {
        while (rule(array[i], p)) {
            ++i;
        }

        while (rule(p, array[j])) {
            --j;
        }

        if (i <= j) {
            swap_record(array[i], array[j]);

            ++i;
            --j;
        }
    }

    if (l < j) {
        sort_set_record_q(array, l, j, rule);
    }

    if (i < r) {
        sort_set_record_q(array, i, r, rule);
    }
}

void sort_quick_recursive(record_t **array, size_t size, sort_rule_t rule) {
    sort_set_record_q(array, 0, size - 1, rule);
}
