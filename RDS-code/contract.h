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


#endif

