#include "objects.h"

person* person_init(char* name, char* first_name, long long CNP)
{	
	person* pers = malloc(sizeof(person));
	strcpy(pers->name, name);	
	strcpy(pers->first_name, first_name);
	pers->cnp = CNP;
	pers->set_cnp = set_person_cnp;
	pers->set_first_name = set_person_first_name;
	pers->set_name = set_person_name;
	pers->print = print_person;
	return pers;
}

void set_person_name(person* pers, char* name)
{
	strcpy(pers->name, name);
}

void set_person_first_name(person* pers, char* first_name)
{
	strcpy(pers->first_name, first_name);
}

void set_person_cnp(person* pers, long long cnp)
{
	pers->cnp = cnp;
}

void print_person(person* pers)
{
	printf("%s %s %lld\n", pers->name, pers->first_name, pers->cnp);
}

bill* bill_init(char* name, char* first_name, char* address, service_type service, long long cnp, struct tm date, int sum)
{
	bill* new_bill = malloc(sizeof(bill));
	new_bill->name = malloc(strlen(name) + 1);
	new_bill->first_name = malloc(strlen(first_name) + 1);
	new_bill->address = malloc(strlen(address) + 1);

	strcpy(new_bill->name, name);
	strcpy(new_bill->first_name, first_name);
	strcpy(new_bill->address, address);
	new_bill->service = service;
	new_bill->cnp = cnp;
	new_bill->date = date;
	new_bill->sum = sum;
	
	return new_bill;
}

void set_bill_name(bill* obj, char* name)
{
	if (obj->name)
	{
		free(obj->name);
	}
	obj->name = malloc(strlen(name) + 1);
	strcpy(obj->name, name);
}

void set_bill_first_name(bill* obj, char* first_name)
{
	if (obj->first_name)
	{
		obj->first_name = realloc(obj->first_name, strlen(first_name) + 1);
	}
	else
	{
		obj->first_name = malloc(strlen(first_name) + 1);
	}
	strcpy(obj->first_name, first_name);
}

void set_bill_address(bill* obj, char* address)
{
	if (obj->address)
	{
		obj->address = realloc(obj->address, strlen(address) + 1);
	}
	else
	{
		obj->address = malloc(strlen(address) + 1);
	}
	strcpy(obj->address, address);
}

phone* init_phone(long long cnp, int number)
{
	phone* new_phone = (phone*)malloc(sizeof(phone));
	new_phone->cnp = cnp;
	new_phone->number = number;
}
