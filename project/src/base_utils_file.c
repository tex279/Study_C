#include <stdio.h>
#include <base_utils_file.h>
#include <std_in_out.h>
#include <base_struct.h>


void clear_file(const char* filename) {
    FILE *fp;
    fp = fopen(filename, "w");
    fclose(fp);
}


int write_to_file(const char *filename, Data *data) {
    FILE *fp;
    fp = fopen(filename, "r+");
    if (!fp) {
        puts("exit");
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    print_data(fp, data);
    //  output(data);
    fclose(fp);
    return 1;
}


int read_from_file(const char *filename, Data *data) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        puts("exit");
        return -1;
    }
    scan_data(fp, data);
    fclose(fp);
    return 1;
}
