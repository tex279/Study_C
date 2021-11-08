#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_


#define ERR_OPEN -1
#define ERR_STAT -2
#define NOT_FIND -3

#define BUF 100

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
char *get_boundary_key(char *source);
char *parser_key_header(char *source, char const *key);
size_t parser_key_parts(char *source);
eml_t *parser(char *source);

// Support
size_t skip_space(char *pos);
char *search_header(char *source, char const *key);
eml_t *parser(char *source);

#endif  //  PROJECT_INCLUDE_PARSER_H_
