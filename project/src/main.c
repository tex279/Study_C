#include "utils.h"
#include "case_4.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3
#define TST_4           4


/* NOTE(stitaevskiy):
 * We use `atoi` function just for simplification and code reducing.
 * This function doesn't report conversation errors.
 * For safety program we recommend using `strtol` and its analogs.
 * (See `man atoi` and `man strtol` for more info).
 *
 * const char str_num[] = "12345";
 * char* end = NULL;
 * int val = (int) strtol(str_num, &end, 0);
 * if (end != '\0') {
 *     //ERROR
 * }
 *
 * */

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int Test_case = atoi(argv[1]);
    const char* data;
    data = argv[2];

    switch (Test_case) {
        case TST_FOO_FIX: {
            int to = atoi(data);
            size_t ticks_count = timer_from(to);
            printf("%zu\n", ticks_count);
            break;
        }
        case TST_FOO_IMPL: {
            if (argc == 4) {
                 int base = atoi(data);
                 int pow =  atoi(argv[3]);
                 int res = custom_pow(base, pow);    // TODO(Alexandr_Anofrikov): Implement me
                 printf("%i\n", res);
            } else {
                return ERR_ARGS_COUNT;
            }
            break;
        }
        case TST_MOD_IMPL: {
             int num = atoi(data);
             Special_printf_of_num(num);
             break;
            // TODO(Alexandr_Anofrikov): Print to stdout `1` if `num` is prime number and `0` otherwise
            // This function MUST be implemented in
            // a separate C-module (not in `main` or `utils` module)
        }
        case TST_4: {
            int end_out = atoi(data);
            if (end_out > 0) {
                for (int i = 1; i <= end_out; ++i) {
                    printf("%d", i);
                    if (i < end_out)
                        printf(" ");
                }
            } else {
                for (int i = 1; i >= end_out; --i) {
                    printf("%d", i);
                    if (i > end_out)
                        printf(" ");
                }
            }
            return 0;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
}
