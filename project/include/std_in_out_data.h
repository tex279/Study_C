#ifndef PROJECT_INCLUDE_STD_IN_OUT_DATA_H_
#define PROJECT_INCLUDE_STD_IN_OUT_DATA_H_

#include <stdio.h>
#include <base_struct.h>

int scan_data(FILE *filename, Data *data);
void print_data(FILE *filename, Data *data);
int input(Data *data);
void output(Data *data);


#endif  //  PROJECT_INCLUDE_STD_IN_OUT_DATA_H_
