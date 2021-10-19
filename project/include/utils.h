#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <base_struct.h>
#include <stdio.h>

void transaction_write(FILE *ofPtr, Data *transfer);
void black_record(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data *client_data, Data *transfer);

#endif  //  PROJECT_INCLUDE_UTILS_H_
