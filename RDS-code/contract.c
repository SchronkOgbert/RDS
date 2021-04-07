#include "contract.h"
#include "core.h"

void createcontract()
{
	clear_console();
	contract option;
	select_service(&option);
	select_type(&option);
	select_years(&option);
	long cnp;
	char* name = NULL;
	char* first_name = NULL;
	char* address = NULL;
	read_cnp(&cnp);
	name = read_name();
	first_name = read_first_name();
	address = read_address();
	if (confirm_data(option, cnp, name, first_name, address)) {
		free(name);
		free(first_name);
		free(address);
		createcontract();
		return;
	}
	free(name);
	free(first_name);
	free(address);
}

void select_service(contract *con)
{
	clear_console();
	printf("Alegeti un serviciu:\n");
	printf("0.Telefon\n");
	printf("1.Televiziune\n");
	printf("Introduceti numarul optiunii: ");
	scanf("%d", &con->service);
}

void select_type(contract *con)
{
	clear_console();
	printf("Alegeti tipul contractului:\n");
	printf("0.Basic\n");
	printf("1.Premium\n");
	printf("Introduceti numarul optiunii: ");
	scanf("%d", &con->type);
}

void select_years(contract* con)
{
	int buffer;
	clear_console();
	printf("Selectati durata abonamentului:\n");
	printf("0.Un an\n");
	printf("1.Doi ani\n");
	printf("Introduceti numarul optiunii: ");
	scanf("%d", &buffer);
	if (buffer == 0)
		con->years = 1;
	else
		con->years = 2;
}
void read_cnp(long* cnp)
{
	clear_console();
	printf("Introduceti CNP-ul: ");
	scanf("%ld", cnp);

}

char* read_name()
{
	char* name;
	char buffer[40];
	clear_console();
	printf("Introduceti numele: ");
	scanf("%s", buffer);
	name = (char*)malloc(strlen(buffer) + 1);
	strcpy(name, buffer);
	return name;
}

char* read_first_name()
{
	char* first_name;		
	char buffer[40];
	clear_console();
	printf("Introduceti prenumele: ");
	scanf("%s", buffer);
	first_name = (char*)malloc(strlen(buffer) + 1);
	strcpy(first_name, buffer);
	return first_name;
}

char* read_address()
{
	char* address;
	char buffer[40];
	clear_console();
	printf("Introduceti adresa: ");
	scanf("%s", buffer);
	address = (char*)malloc(strlen(buffer) + 1);
	strcpy(address, buffer);
	return address;
}

int confirm_data(contract con, long cnp, char* name, char* first_name, char* address)
{
	clear_console();
	printf("Sunt corecte datele acestea?\n");
	printf("Nume: %s\n", name);
	printf("Prenume: %s\n", first_name);
	printf("CNP: %ld\n", cnp);
	printf("Adresa: %s\n", address);
	if (con.service == Phone) {
		printf("Tipul serviciului: Telefonie\n");
	
	}
	else {
		printf("Tipul serviciului: Televiziune\n");
	}
	if (con.type == Basic) {
		printf("Tipul contractului: Basic\n");
	}
	else {
		printf("Tipul contractului: Premium\n");
	}
	printf("Durata abonamentului: %d\n", con.years);
	printf("Confirmati datele?\n");
	printf("0. Da\n");
	printf("1. Nu\n");
	printf("Introduceti numarul optiunii: ");
	int option;
	scanf("%d", &option);
	return option;
}
