#include <stdio.h>

#include <std_in_out_data.h>

int scan_data(FILE *filename, fin_profile_t *data) {
    if (!(fscanf(filename, "%d%20s%20s%30s%15s%lf%lf%lf",
               &data->number,
               data->name,
               data->surname,
               data->address,
               data->tel_number,
               &data->indebtedness,
               &data->credit_limit,
               &data->cash_payments) != -1)) {
        return INCORRECT_INPUT;
    }
    return SUCCESS;
}

void print_data(FILE *filename, fin_profile_t *data) {
    fprintf(filename, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            data->number,
            data->name,
            data->surname,
            data->address,
            data->tel_number,
            data->indebtedness,
            data->credit_limit,
            data->cash_payments);
}

int input(fin_profile_t *data) {
    fprintf(stdout, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
            "1 number account: ",
            "2 Client name: ",
            "3 surname: ",
            "4 address client: ",
            "5 Client Telnum: ",
            "6 Client indebtedness: ",
            "7 Client credit limit: ",
            "8 Client cash payments: ");
    if (!scan_data(stdin, data)) {
        return INCORRECT_INPUT;
    }
    return SUCCESS;
}

void output(fin_profile_t *data) {
    fprintf(stdout, "%d %20s %20s %30s %15s %f %f %f\n",
           data->number,
           data->name,
           data->surname,
           data->address,
           data->tel_number,
           data->indebtedness,
           data->credit_limit,
           data->cash_payments);
}

