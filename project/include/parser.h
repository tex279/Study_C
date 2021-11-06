#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <stddef.h>
#include <stdio.h>

#define MAX_LENGTH_STR 255

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
int part;
} eml_t;

eml_t *create_eml(void);
void free_eml(eml_t *data);
char *search_value(char const *source, char const *key);
char *get_value(char const *source, char const *pos);
char *parser_key(char const *str, char const *key);
int parser(FILE *filename);

// Utils
eml_t *create_eml(void);
void output(eml_t *data);
void free_eml(eml_t *data);

//  Support
size_t check_zero_end(char const *source, char const *pos);
size_t skip_space(char *pos);
char *rm_apst(char const *source);
char *check_type_eml(char const *str);

#endif  //  PROJECT_INCLUDE_PARSER_H_
