#include <stdio.h>
#include <w_r_file.h>
#include <std_in_out_data.h>
#include <utils_for_file.h>

int transaction_write(const char *filename, Data *transfer) {
    FILE *ofptr = fopen(filename, "w+r");
    if (!ofptr) {
        fprintf(stdout, "%s\n", "error");
        return ERROR_OPEN_FILE;
    }
    printf("%s\n%s\n",
           "1 number account: ",
           "2 Client cash payments: ");
    while (fscanf(stdin, "%d%lf",
                  &transfer->number,
                  &transfer->cash_payments) != -1) {
        fprintf(ofptr, "%-3d%-6.2f\n",
                transfer->number,
                transfer->cash_payments);
    }
    fclose(ofptr);
    return SUCCESS;
}

int black_record(const char *filename_out_general,
                  const char *filename_out,
                  const char *filename_update,
                  Data *client_data,
                  Data *transfer) {
    FILE *ptr = fopen(filename_out_general, "r");
    FILE *ptr_2 = fopen(filename_out, "r");
    FILE *ptr_3 = fopen(filename_update, "w");
    if (!ptr || !ptr_2 || !ptr_3) {
        fprintf(stdout, "%s\n", "error");
        return ERROR_OPEN_FILE;
    }
    while (scan_data(ptr, client_data)) {
        while (fscanf(ptr_2, "%d%lf\n",
                      &transfer->number,
                      &transfer->cash_payments) != -1) {
            if ((client_data->number == transfer->number) != 0) {
                client_data->credit_limit += transfer->cash_payments;
                print_data(ptr_3, client_data);
            }
        }
        rewind(ptr_2);
    }
    fclose(ptr);
    fclose(ptr_2);
    fclose(ptr_3);
    return SUCCESS;
}

