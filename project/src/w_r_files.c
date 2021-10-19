#include <stdio.h>
#include <w_r_files.h>

void write_to_file(const char *filename, Some *data) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        puts("exit");
    } else {
        fprintf(fp, "%-8d%-20s",
                data->id,
                data->Name);
        fclose(fp);
    }
}

void read_from_file(const char *filename, Some *data) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        puts("exit");
    } else {
        fscanf(fp, "-%8d-%20s",
               &data->id,
               data->Name);
        fclose(fp);
    }
}
