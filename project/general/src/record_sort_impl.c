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
        }

        return false;
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



void quick_sort_base(record_t **array, size_t l, size_t r, const sort_rule_t rule) {
    size_t i = l;
    size_t j = r;

    record_t **pp = create_set_record(3);
    if (!pp) {
        fprintf(stderr, "memory allocation error\n");
    }

    copy_record(pp[0], array[l]);
    copy_record(pp[1], array[r]);
    copy_record(pp[2], array[(l + r) >> 1]);

    print_record(stdout, pp[0]);
    fprintf(stdout, "%zu\n", strlen(pp[0]->position));
    print_record(stdout, pp[1]);
    fprintf(stdout, "%zu\n", strlen(pp[1]->position));
    print_record(stdout, pp[2]);
    fprintf(stdout, "%zu\n", strlen(pp[2]->position));

    if (rule(pp[0], pp[1]))  {
        swap_record(pp[0], pp[1]);
    }

    if (rule(pp[1], pp[2])) {
        swap_record(pp[1], pp[2]);
    }

    if (rule(pp[0], pp[1])) {
        swap_record(pp[0], pp[1]);
    }

    record_t *p = *create_set_record(1);

    copy_record(p, pp[1]);

    print_record(stdout, pp[2]);
    fprintf(stdout, "%zu\n", strlen(pp[2]->position));

    fprintf(stdout, "BEFORE\n");

    while (i <= j) {
        while (!rule(p, array[i]))
            i++;

        while (!rule(array[j], p))
            j--;

        if (i <= j) {
            swap_record(array[i], array[j]);

            i++;
            j--;
        }
    }
    fprintf(stdout, "AFTER\n");

    free_set_record(pp, 3);

    free(p);

    if (l < j) {
        quick_sort_base(array, l, j, rule);
    }

    if (i < r) {
        quick_sort_base(array, i, r, rule);
    }
}


void sort_set_record_q(record_t **array, const size_t number_records, const sort_rule_t rule) {
    quick_sort_base(array, 0, number_records - 1, rule);
}