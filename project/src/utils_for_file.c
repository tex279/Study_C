#include <stdio.h>

#include <w_r_file.h>
#include <std_in_out_data.h>
#include <utils_for_file.h>


int input_transaction(fin_profile_t *data) {
    if (!(fscanf(stdin, "%d%lf",
               &data->number,
               &data->cash_payments)!= -1)) {
        return INCORRECT_INPUT;
    }
    return SUCCESS;
}

int transaction_write(const char *filename, fin_profile_t *transfer_data) {
    FILE *target = fopen(filename, "w+r");
    if (!target) {
        fprintf(stdout, "%s\n", "error");
        return ERROR_OPEN_FILE;
    }
    fprintf(stdout, "%s\n%s\n",
            "1 number account: ",
            "2 Client cash payments: ");
    while (input_transaction(transfer_data)) {
        fprintf(target, "%-3d%-6.2f\n",
                transfer_data->number,
                transfer_data->cash_payments);
    }
    fclose(target);
    return SUCCESS;
}

int rerecord(const char *filename_source,
             const char *filename_source_upd,
             const char *filename_target,
             fin_profile_t *client_data,
             fin_profile_t *transfer_data) {
    FILE *sourse = fopen(filename_source, "r");
    FILE *sourse_upd = fopen(filename_source_upd, "r");
    FILE *target = fopen(filename_target, "w");
    if (!sourse || !sourse_upd || !target) {
        fprintf(stdout, "%s\n", "error");
        return ERROR_OPEN_FILE;
    }
    while (scan_data(sourse, client_data)) {
        while (fscanf(sourse_upd, "%d%lf\n",
                      &transfer_data->number,
                      &transfer_data->cash_payments) != -1) {
            if ((client_data->number == transfer_data->number) != 0) {
                client_data->credit_limit += transfer_data->cash_payments;
                print_data(target, client_data);
            }
        }
        rewind(sourse_upd);
    }
    fclose(sourse);
    fclose(sourse_upd);
    fclose(target);
    return SUCCESS;
}

