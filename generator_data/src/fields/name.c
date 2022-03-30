#include <stddef.h>

#include "fields.h"

#include "utils.h"

const char *female_name[32] = {
        "Anna",
        "Anastasia",
        "Alana",
        "Alexandra",
        "Alice",
        "Chantal",
        "Elizabeth",
        "Holly",
        "Victoria"
};

const char *male_name[32] = {
        "Adam",
        "Anthony",
        "Clinton",
        "Dirk",
        "Earl",
        "Elliot",
        "James",
        "Jasper",
        "Winston"
};

const char **get_name(const bool gender) {
    if (gender) {
        return get_value(female_name, get_rand_number(0, sizeof(*male_name) + 1));
    }

    return get_value(male_name, get_rand_number(0, sizeof(*male_name) + 1));
}

