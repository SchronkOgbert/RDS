#ifndef CONTRACT
#define CONTRACT
#include "objects.h"

typedef enum account_type {
	Basic,Premium
}account_type;
typedef struct contract {
	service_type service;
	account_type type;
	int years;
}contract;
void createcontract();
void select_service(contract *con);
void select_type(contract *con);
void select_years(contract* con);
void read_cnp(long long* cnp);
char* read_name();
char* read_first_name();
char* read_address();
int confirm_data(contract con, long long cnp, char* name, char* first_name, char* address);
void submit_data(contract option, long long cnp, char* name, char* first_name, char* address);

#endif

