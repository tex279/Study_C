#include <stdio.h>
#include <w_r_file.h>
#include <std_in_out_data.h>
#include <base_struct.h>

int write_to_file(const char *filename, Data *data) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stdout, "%s\n", "error from foo write to file");
        return ERROR_OPEN_FILE;
    }
    while (input(data)) {
        print_data(fp, data);
    }
    fclose(fp);
    return SUCCESS;
}


int read_from_file(const char *filename, Data *data) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stdout, "%s\n", "error from foo read from file");
        return ERROR_OPEN_FILE;
    }
    while (scan_data(fp, data)) {}
    fclose(fp);
    return SUCCESS;
}
