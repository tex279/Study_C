#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "utils.h"

const char **get_value(const char **source, const size_t target) {
    fprintf(stdout, "%zu\n", target);
    fprintf(stdout, "%s\n", source[target]);
    return &source[target];
}

size_t get_rand_number(const size_t min, const size_t max) {
    return (min + rand() % (max - min + 1));
}

bool get_variant() {
    if (get_rand_number(0, 1)) {
        return true;
    }

    return false;
}
