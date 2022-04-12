#pragma once //  NOLINT

#include <stddef.h>

#define ERR_OPEN_FILE -1
#define ERR_CREATE_FILE -2
#define ERR_WRITE_FILE -3
#define ERR_CLOSE_FILE -4

#define ERR_ALOC_M "memory allocation error\n"

#define ERR_OPEN_F_READ_M "error open file for read\n"
#define ERR_OPEN_F_WRITE_M "error open file for write\n"
#define ERR_CLOSE_F_M "failed close file\n"

#define ERR_READ_FIELD_M "error get field\n"
#define ERR_READ_RECORD_M "error get record\n"

#define ERR_INPUT_M "incorrect input\n"
#define ERR_CONVERSION_M "error conversion str to number\n"

#define ERR_CREATE_SET_FORMATS_M "error create set formats\n"
#define ERR_CREATE_SET_RECORDS_M "error create set records\n"
#define ERR_LOAD_DATA_M "error load data\n"
#define ERR_GENERATE_M "error generate data\n"

#define ERR_ALOCC -2

char *create_str(const char *source);

char *create_format(const size_t size_str, const size_t size_format);
