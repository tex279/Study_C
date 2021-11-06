#ifndef PROJECT_INCLUDE_UTILS_FOR_FILE_H_
#define PROJECT_INCLUDE_UTILS_FOR_FILE_H_

#include <base_struct.h>

int input_transaction(fin_profile_t *data);
int transaction_write(const char *filename, fin_profile_t *transfer_data);
int rerecord(const char *filename_source,
             const char *filename_source_upd,
             const char *filename_target,
             fin_profile_t *client_data,
             fin_profile_t *transfer_data);

#endif  //  PROJECT_INCLUDE_UTILS_FOR_FILE_H_
