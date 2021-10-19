#ifndef PROJECT_INCLUDE_W_R_FILES_H_
#define PROJECT_INCLUDE_W_R_FILES_H_

struct some {
    int 		id;
    char 		Name[20];
};

typedef  struct  some Some;

void write_to_file(const char *filename, Some *data);
void read_from_file(const char *filename, Some *data);

#endif  //  PROJECT_INCLUDE_W_R_FILES_H_
