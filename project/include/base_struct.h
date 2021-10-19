#ifndef  PROJECT_INCLUDE_BASE_STRUCT_H_
#define  PROJECT_INCLUDE_BASE_STRUCT_H_

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


#endif  //   PROJECT_INCLUDE_BASE_STRUCT_H_
