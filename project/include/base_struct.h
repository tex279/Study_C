#ifndef  PROJECT_INCLUDE_BASE_STRUCT_H_
#define  PROJECT_INCLUDE_BASE_STRUCT_H_

#define LENGTH_NAME         20
#define LENGTH_SURNAME      20
#define LENGTH_ADDRESS      30
#define LENGTH_TELNUMBER    15


struct master_record {
    int 		Number;
    char 		Name[LENGTH_NAME];
    char 		Surname[LENGTH_SURNAME];
    char 		Address[LENGTH_ADDRESS];
    char        TelNumber[LENGTH_TELNUMBER];
    double  	Indebtedness;
    double    	Credit_limit;
    double  	Cash_payments;
};

typedef  struct  master_record Data;


#endif  //   PROJECT_INCLUDE_BASE_STRUCT_H_
