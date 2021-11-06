#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <parser.h>

int main(int argc, char const **argv) {
    if (argc != 2) {
        fprintf(stdout, "incorrect input\n");
        return -1;
    }
    char const *path_to_eml = argv[1];

    FILE* source = fopen(path_to_eml, "r");

    if (!source) {
        fprintf(stderr, "file cannot be opened\n");
        return -1;
    }

    parser(source);

    fclose(source);
    return 0;
}
