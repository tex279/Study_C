#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_


#define ERR_OPEN -1
#define ERR_STAT -2
#define NOT_FIND -3

#define MAX_LENGTH_STR 1000

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

//  Parser
size_t check_header(char const *source, size_t const pos);
char *parser_key_header(char const *source, char const *key, size_t const flag_rule);
eml_t *parser(char const *source);

// Support
size_t skip_space(char const *source, size_t const pos);
char *create_str(size_t const length);
int cmp_str(size_t const begin, char const *source, char const *key);
int search(size_t const begin, char const *source, char const *key);
char *get_value(char const *source, size_t const pos);
eml_t *parser(char const *source);
char *rm_aptr(char const *value);

#endif  //  PROJECT_INCLUDE_PARSER_H_
