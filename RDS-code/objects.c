#include "objects.h"

person* person_init(char* name, char* first_name, long CNP)
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

void set_person_cnp(person* pers, long cnp)
{
	pers->cnp = cnp;
}

void print_person(person* pers)
{
	printf("%s %s %ld\n", pers->name, pers->first_name, pers->cnp);
}
