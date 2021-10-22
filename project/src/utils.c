#include <stdio.h>
#include <base_utils_file.h>
#include <std_in_out.h>
#include <utils.h>


int transaction_write(const char *filename, Data *transfer) {
    FILE *ofPtr;
    ofPtr = fopen(filename, "w+r");
    if (!ofPtr) {
        puts("exit");
        return -1;
    } else {
        printf("%s\n%s\n",
               "1 Number account: ",
               "2 Client cash payments: ");
        while (scanf( "%d%lf",
                      &transfer->Number,
                      &transfer->Cash_payments) != -1) {
            fprintf(ofPtr, "%-3d%-6.2f\n",
                    transfer->Number,
                    transfer->Cash_payments);
        }
        fclose(ofPtr);
        return 1;
    }
}

int black_record(const char *filename_out_general,
                  const char *filename_out,
                  const char *filename_update,
                  Data *client_data,
                  Data *transfer) {
    FILE *ptr, *ptr_2;
    ptr = fopen(filename_out_general, "r");
    ptr_2 = fopen(filename_out, "r");
    if (!ptr || !ptr_2) {
        puts("exit");
        return -1;
    } else {
        while (scan_data(ptr, client_data)) {
            while (fscanf(ptr_2, "%d%lf\n",
                          &transfer->Number,
                          &transfer->Cash_payments) != -1) {
                if ((client_data->Number == transfer->Number) != 0) {
                    client_data->Credit_limit += transfer->Cash_payments;
                    write_to_file(filename_update, client_data);
                }
            }
            rewind(ptr_2);
        }
        fclose(ptr);
        fclose(ptr_2);
        return 1;
    }
}

