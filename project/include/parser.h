#pragma once //  NOLINT

#include <stdlib.h>

#define MAX_LENGTH_COMPARE 250

#define FROM "From:"
#define TO "To:"
#define DATE "Date:"
#define TYPE "Content-Type:"

#define MULTIPART "multipart/"
#define BOUNDARY "boundary="

typedef struct {
    char *source;
    char *target;
    char *date;
    size_t parts;
} eml_t;

// Support
void free_eml(eml_t *eml);
void print_eml(eml_t *eml);
size_t skip_space(char *pos);
size_t check_str(char  *in);
char *get_value_header(char const *source, char const *end);
char *get_boundary_key(char *source);

//  Main
char *search_begin_header(char *source, char const *key);
char *search_end_header(char *source);
char *parser_key_header(char *source, char const *key);
size_t parser_key_parts(char *source);
eml_t *parser(char *source);
