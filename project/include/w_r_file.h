#ifndef PROJECT_INCLUDE_W_R_FILE_H_
#define PROJECT_INCLUDE_W_R_FILE_H_

#include <base_struct.h>

int write_to_file(const char *filename, fin_profile_t *data);
int read_from_file(const char *filename, fin_profile_t *data);

#endif  //  PROJECT_INCLUDE_W_R_FILE_H_
