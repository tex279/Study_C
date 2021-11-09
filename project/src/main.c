#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <parser.h>

int main(int argc, char const **argv) {
    if (argc != 2) {
        fprintf(stdout, "incorrect input\n");
        return -1;
    }
    char const *path_to_eml = argv[1];

    int file = open(path_to_eml, O_RDONLY);
    if (file == -1) {
        fprintf(stderr, "file cannot be opened\n");
        return ERR_OPEN;
    }

    char *data = NULL;

    struct stat buf = { };
    if (fstat(file, &buf) == -1) {
        fprintf(stderr, "impossible to get the status\n");
        return ERR_STAT;
    }

    data = (char *)mmap(0, buf.st_size, PROT_READ, MAP_SHARED, file, 0);
    if (data == MAP_FAILED) {
        return -1;
    }

    eml_t *eml = parser(data);

    print_eml(eml);

    return 0;
}
