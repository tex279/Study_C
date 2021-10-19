#ifndef TECHPARK_2021_STRUCT___CONST_H
#define TECHPARK_2021_STRUCT___CONST_H

struct masterRecord {
    int 		Number;
    char 		Name[20];
    char 		Surname[20];
    char 		address[30];
    char        TelNumber[15];
    double  	indebtedness;
    double    	credit_limit;
    double  	cash_payments;
};

typedef  struct  masterRecord Data;

Data client_data, transfer;

#endif //TECHPARK_2021_STRUCT___CONST_H
