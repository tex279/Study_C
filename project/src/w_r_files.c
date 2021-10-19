#include <stdio.h>
#include <w_r_files.h>

struct some {
    int 		id;
    char 		Name[20];
};

void write_to_file(const char *filename, struct some *data) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file \n")
    }
    fprintf(fp, "%-8d%-20s",
            data.id,
            data.Name);
    fclose(fp);
}

void read_from_file(const char *filename, struct some *data) {
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file \n")
    }
    fscanf(fp, "-%8d-%20s",
            data.id,
            data.Name);
    fclose(fp);
}