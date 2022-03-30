#include <stddef.h>

#include "fields.h"

#include "utils.h"

const char **get_name(const bool gender) {
    if (gender) {
        return get_value(female_name, get_rand_number(0, sizeof(*male_name) + 1));
    }

    return get_value(male_name, get_rand_number(0, sizeof(*male_name) + 1));
}

const char **get_surname(const bool gender) {
    bool type_surname = get_variant();

    if (gender) {
        if (type_surname) {
            return get_value(female_surname, get_rand_number(0, sizeof(*female_surname) + 1));
        }

        return get_value(female_surname, get_rand_number(0, sizeof(*surname) + 1));
    }

    if (type_surname) {
        return get_value(male_surname, get_rand_number(0, sizeof(*male_surname) + 1));
    }

    return get_value(male_surname, get_rand_number(0, sizeof(*surname) + 1));
}

const char **get_position() {
    return get_value(position, get_rand_number(0, sizeof(*position) + 1));
}
