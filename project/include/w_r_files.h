#ifndef TECHPARK_2021_W_R_FILES_H
#define TECHPARK_2021_W_R_FILES_H

struct some {
    int 		id;
    char 		Name[20];
};

typedef  struct  some Some;

void write_to_file(const char *filename, Some *data);
void read_from_file(const char *filename, Some *data);

#endif  //  TECHPARK_2021_W_R_FILES_H
