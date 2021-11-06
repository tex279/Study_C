#include <stdio.h>

#include <w_r_file.h>
#include <std_in_out_data.h>
#include <base_struct.h>

int write_to_file(const char *filename, fin_profile_t *data) {
    FILE *target = fopen(filename, "w");
    if (!target) {
        fprintf(stderr, "%s\n", "error write to file");
        return ERROR_OPEN_FILE;
    }
    while (input(data)) {
        print_data(target, data);
    }
    fclose(target);
    return SUCCESS;
}


int read_from_file(const char *filename, fin_profile_t *data) {
    FILE *target = fopen(filename, "r");
    if (!target) {
        fprintf(stderr, "%s\n", "error from foo read from file");
        return ERROR_OPEN_FILE;
    }
    while (scan_data(target, data)) {}
    fclose(target);
    return SUCCESS;
}
