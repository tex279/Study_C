#include <stdio.h>
#include <base_utils_file.h>
#include <std_in_out.h>
#include <base_struct.h>


void clear_file(const char* filename) {
    FILE *fp;
    fp = fopen(filename, "w");
    fclose(fp);
}


int write_to_file(const char *filename, Data *data) {
    FILE *fp;
    fp = fopen(filename, "r+");
    if (!fp) {
        puts("exit");
        return -1;
    } else {
        fseek(fp, 0, SEEK_END);
        fprintf(fp, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                data->Number,
                data->Name,
                data->Surname,
                data->Address,
                data->TelNumber,
                data->Indebtedness,
                data->Credit_limit,
                data->Cash_payments);
        output(data);
        fclose(fp);
        return 1;
    }
}


int read_from_file(const char *filename, Data *data) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        puts("exit");
        return -1;
    } else {
        if (fscanf(fp, "%d%20s%20s%30s%15s%lf%lf%lf\n",
               &data->Number,
               data->Name,
               data->Surname,
               data->Address,
               data->TelNumber,
               &data->Indebtedness,
               &data->Credit_limit,
               &data->Cash_payments) != -1) {
            output(data);
        }
        fclose(fp);
        return 1;
    }
}
