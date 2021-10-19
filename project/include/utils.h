#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <base_struct.h>

void transaction_write(const char *filename, Data *transfer);
void black_record(const char *filename_out_general,
                  const char *filename_out,
                  const char *filename_update,
                  Data *client_data,
                  Data *transfer);

#endif  //  PROJECT_INCLUDE_UTILS_H_
