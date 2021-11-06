#include <stdlib.h>

#include <parser.h>

eml_t *create_eml(void) {
    eml_t *eml = (eml_t*)calloc(1, sizeof(eml_t));

    if (!eml) {
        fprintf(stderr, "failed to allocate memory\n");
        return NULL;
    }

    return eml;
}

void output(eml_t *data) {
    fprintf(stdout, "%s|%s|%s|%d\n", data->source, data->target, data->date, data->part);
}

void free_eml(eml_t *data) {
    free(data->source);
    free(data->target);
    free(data->date);
    free(data);
}