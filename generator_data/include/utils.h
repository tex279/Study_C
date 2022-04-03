#pragma once //  NOLINT

#define ERR_ACOC -1

#define ERR_OPEN_FILE -1
#define ERR_CLOSE_FILE -2
#define ERR_READ -3

//  base
char *create_str(const char *source);

char *create_format(const size_t size_str, const size_t size_format);

