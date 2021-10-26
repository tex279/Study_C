#ifndef PROJECT_INCLUDE_UTILS_FOR_FILE_H_
#define PROJECT_INCLUDE_UTILS_FOR_FILE_H_

#include <base_struct.h>

int input_transaction(Data *data);
int transaction_write(const char *filename, Data *transfer);
int black_record(const char *filename_out_general,
                  const char *filename_out,
                  const char *filename_update,
                  Data *client_data,
                  Data *transfer);

#endif  //  PROJECT_INCLUDE_UTILS_FOR_FILE_H_
