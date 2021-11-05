#ifndef PROJECT_INCLUDE_STD_IN_OUT_DATA_H_
#define PROJECT_INCLUDE_STD_IN_OUT_DATA_H_

#include <stdio.h>
#include <base_struct.h>

int scan_data(FILE *filename, fin_profile_t *data);
void print_data(FILE *filename, fin_profile_t *data);
int input(fin_profile_t *data);
void output(fin_profile_t *data);

#endif  //  PROJECT_INCLUDE_STD_IN_OUT_DATA_H_
