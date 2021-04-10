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
	}
	else
	{
		submit_data(option, cnp, name, first_name, address);
		printf("Contract creat.\n");
	}	
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

void submit_data(contract option, long cnp, char* name, char* first_name, char* address)
{
	int sub_index = 1;
	if (option.service == Cable)
	{
		sub_index += 4;
	}
	if (option.type == Premium)
	{
		sub_index += 2;
	}
	if (option.years == 2)
	{
		sub_index++;
	}
	if (!does_client_exist(cnp))
	{
		char* columns[4];
		columns[0] = name;
		columns[1] = first_name;
		columns[2] = long_to_string(cnp);
		columns[3] = address;
		add_person(name, first_name, cnp);
		append_to_csv(CLIENTS, 4, columns);		
		free(columns[2]);
	}
	
	char* columns[2];
	columns[0] = long_to_string(cnp);
	columns[1] = int_to_string(sub_index);
	append_to_csv(SUBSCRIPTIONS, 2, columns);
	free(columns[1]);
	if (option.service == Phone)
	{
		map_phones();
		char* tmp = get_config_property("current_number");
		int suffix = string_to_long(tmp);
		char number[11] = "07";
		strcat(number, tmp);
		columns[1] = number;
		append_to_csv(PHONES, 2, columns);
		tmp = int_to_string(suffix + 1);
		//what imma do now isn't very good but it gets the job done
		FILE* conf = fopen(CONFIG, "w");
		if (conf)
		{
			fprintf(conf, "current_number:%s", tmp);
		}
		else
		{
			printf("could not open file...\n");
		}
		fclose(conf);
		free(tmp);
	}
	free(name);
	free(first_name);
	free(address);
}
