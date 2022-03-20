#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "utils.h"
#include "check_num.h"
#include "my_rec.h"

#define ERR_ARGS_COUNT      -1
#define ERR_WRONG_FLG       -2
#define ERR_CONVERT_STR     -3

#define TST_FOO_FIX         1
#define TST_FOO_IMPL        2
#define TST_MOD_IMPL        3
#define TST_FOO_REC         4

#define COUNT_ARG_POW       4

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    char* end_convert = NULL;
    int test_case = strtol(argv[1], &end_convert, 0);
    if (*end_convert != '\0') {
        return ERR_CONVERT_STR;
    }

    int data = strtol(argv[2], &end_convert, 0);
    if (*end_convert != '\0') {
        return ERR_CONVERT_STR;
    }

    switch (test_case) {
        case TST_FOO_FIX: {
            printf("%zu\n", timer_from(data));
            break;
        }

        case TST_FOO_IMPL: {
            if (argc == COUNT_ARG_POW) {
                int pow =  strtol(argv[3], &end_convert, 0);
                if (*end_convert != '\0') {
                    return ERR_CONVERT_STR;
                }

                printf("%i\n", custom_pow(data, pow));
                break;
            }

            return ERR_ARGS_COUNT;
        }
        case TST_MOD_IMPL: {
             printf("%d\n", check_prime_num(data));
             break;
        }
        case TST_FOO_REC: {
            row_num(data);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }

    return EXIT_SUCCESS;
}
