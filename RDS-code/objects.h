#ifndef OBJ
#define OBJ
#include "libs.h"

typedef struct person person;

struct person
{
	char name[41];
	char first_name[41];
	long cnp;
	void(*set_cnp)(person*, long);
	void(*set_first_name)(person*, char*);
	void(*set_name)(person*, char*);
	void(*print)(person*);
};

person* person_init(char* name, char* first_name, long CNP);
void set_person_name(person* pers, char* name);
void set_person_first_name(person* pers, char* first_name);
void set_person_cnp(person* pers, long cnp);
void print_person(person* pers);


#endif