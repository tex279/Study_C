#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 64

#define LENGTH_STRING_FORMAT 10

#define ERR_OPEN_FILE -1
#define ERR_CREATE_FILE -2
#define ERR_WRITE_FILE -3
#define ERR_CLOSE_FILE -4

char *create_str(const char *source) {
    size_t len = strlen(source);

    char *tmp = calloc(len + 1, sizeof(char));
    if (!tmp) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    tmp = strncpy(tmp, source, len);

    tmp[len] = '\0';

    return tmp;
}

char *create_format(const size_t size_str, const size_t size_format) {
    char *format = calloc(size_format + 1, sizeof(char));
    if (!format) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    snprintf(format, size_format + 1, "%%%zus", size_str);

    return format;
}

char **get_set(const char *source) {
    FILE *flow_source = fopen(source, "r");
    if (!flow_source) {
        fprintf(stderr, "error open file for read");
        return NULL;
    }

    size_t count = 0;
    fscanf(flow_source, "%zu", &count);

    char **set = calloc(count, sizeof(char*));
    if (!set) {
        fprintf(stderr, "memory allocation error\n");
        return NULL;
    }

    char *format = create_format(BUF_SIZE, LENGTH_STRING_FORMAT);
    if (!format) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        char buf[BUF_SIZE];

        if (fscanf(flow_source, format, buf) != 1) {
            free(format);
            return NULL;
        }

        set[i] = create_str(buf);
    }

    free(format);

    if (fclose(flow_source)) {
        fprintf(stderr, "failed close file");
        return NULL;
    }

    return set;
}

void free_set(char **set) {
    for (size_t i = 0; i < sizeof(set) + 1; ++i) {
        free(set[i]);
    }

    free(set);
}

size_t get_rand_number(const size_t min, const size_t max) {
    return (min + rand() % (max - min + 1));
}

char *get_rand_value(char **source, const size_t min, const size_t max) {
    return source[get_rand_number(min, max)];
}
