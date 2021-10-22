#ifndef PROJECT_INCLUDE_BASE_UTILS_FILE_H_
#define PROJECT_INCLUDE_BASE_UTILS_FILE_H_


#include <base_struct.h>

void clear_file(const char* filename);
int write_to_file(const char *filename, Data *data);
int read_from_file(const char *filename, Data *data);


#endif  //  PROJECT_INCLUDE_BASE_UTILS_FILE_H_
