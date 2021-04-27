#include "core.h"
#include "contract.h"

int option;

void startmsg();
void showmenu();
void printclient();
void abonament_tel();
void print_file();
void get_phone_contract();


int main()
{
	
	setup(); //this function needs to be the first line to be executed

	//print_phone_contracts(123456);

	startmsg();

	while ((option > 0 && option < 6) || option == 10)
	{
		switch (option)
		{
		case 1:
		{			
			printclient();
			break;
		}
		case 2:
		{
			get_phone_contract();
			break;
		}
		case 3:
		{
			abonament_tel();
			break;
		}
		case 4:
		{
			createcontract();
			break;
		}
		case 5:
		{
			print_file();
			break;
		}
		case 10:
		{
			secret();
			break;
		}
		}
		system("pause");
		clear_console();
		showmenu();
	}
	clear_console();
	printf("Go ahead and leave. See if I care.\n");
	prepare_quit(); //this function needs to be last to be executed

	system("pause");

	return 0;
}

void startmsg()
{
	printf("Bine ati venit la TmRDS!\n");
	showmenu();
}

void showmenu()
{
	printf("Va rugam alegeti optiunea:\n");
	printf("1.Afisati pentru fiecare abonat numele, adresa si suma de plata pe luna curenta.\n");
	printf("2.Afisati abonamentele telefonice.\n");
	printf("3.Afisati numarul de abonati care au abonament la cel putin 3 numere de telefon.\n");
	printf("4.Creeaza un contract.\n");
	printf("5.Afisati continutul unui fisier.\n");
	printf("6.Inchideti aplicatia.\n");
	printf("Introduceti numarul optiunii: ");
	scanf("%d", &option);
	printf("\n");
}

void printclient()
{
	clear_console();
	if (!people_count)
	{
		printf("Nu exista clienti in baza de date...\n\n");
		return;
	}
	for (int i = 0; i < people_count; i++)
	{
		set_bill_data(search_bills(people[i]->cnp));
		int sum = 0;
		for (int j = 0; j < bill_count; j++)
		{
			sum += bill_data[j]->sum;
		}
		if(bill_data)
			printf("%s %s: %s, %d\n", bill_data[0]->name, bill_data[0]->first_name, bill_data[0]->address, sum);
	}
	
}

void abonament_tel()
{
	int contor = 0;
	for (int i = 0; i < people_count; i++)
	{
		int index = has_phone(people[i]->cnp);
		if (index > -1)
		{
			if (phones[index]->number > 2)
				contor++;
		}
	}
	printf("Numarul de persoane cu cel putin 3 numere de telefon este: %d\n", contor);
}


void print_file()
{
	clear_console();
	char filename[32];
	printf("Introduceti numele fisierului: ");
	scanf("%s", filename);
	char* buffer = _strdup(filename);
	strcpy(filename, "db/");
	strcat(filename, buffer);
	print_file_content(filename);
}
void get_phone_contract()
{
	clear_console();
	for (int i = 0; i < people_count; i++)
	{
		printf("Clientul %s %s are urmatoarele abonamente de telefon:\n", people[i]->name, people[i]->first_name);
		print_phone_contracts(people[i]->cnp);
		if (i < people_count - 1)
		{
			printf("===================================================================\n");
		}
	}
}


