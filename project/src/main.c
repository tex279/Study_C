#include "utils.h"
#include "check_num.h"
#include "my_rec.h"
#include "stdio.h"
#include "stddef.h"
#include "stdlib.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_FOO_REC     4


int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    char* end = NULL;
    int Test_case = strtol(argv[1], &end, 0);
    const char* data;
    data = argv[2];

    switch (Test_case) {
        case TST_FOO_FIX: {
            int to = strtol(data, &end, 0);
            size_t ticks_count = timer_from(to);
            printf("%zu\n", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc == 4) {
                 int base = strtol(data, &end, 0);
                 int pow =  strtol(argv[3], &end, 0);
                 int res = custom_pow(base, pow);
                 printf("%i\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
            break;
        }
        case TST_MOD_IMPL: {
             int num = strtol(data, &end, 0);
             check_prime_num(num);
             break;
        }
        case TST_FOO_REC: {
            int num = strtol(data, &end, 0);
            int pos = 1;
            direct(num, pos);
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
