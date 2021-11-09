#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <stdlib.h>

#define MAX_LENGTH_COMPARE 100

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

void free_eml(eml_t *eml);
void print_eml(eml_t *eml);

size_t skip_space(char *pos);
size_t check_str(char const *in);
char *search_header(char *source, char const *key);
char *parser_key_header(char *source, char const *key);
char *get_boundary_key(char *source);
size_t parser_key_parts(char *source);
eml_t *parser(char *source);

#endif  //  PROJECT_INCLUDE_PARSER_H_
