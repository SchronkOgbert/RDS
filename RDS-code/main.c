#include "core.h"

int option;

void startmsg();
void showmenu();

int main()
{
	setup(); //this function needs to be the first line to be executed


	startmsg();

	while (option < 5)
	{
		switch (option)
		{
		case 1:
		{
			//aici vine functia
			showmenu();
			break;
		}
		case 2:
		{
			//aici vine functia
			break;
		}
		case 3:
		{
			//aici vine functia
			break;
		}
		case 4:
		{
			//aici vine functia
			break;
		}

		}
	}

	prepare_quit(); //this function needs to be last to be executed

	//system("pause");

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
	printf("1.Cautati suma de plata dupa cnp.\n");
	printf("2.Afisati abonamentele telefonice.\n");
	printf("3.Afisati numarul de abonati care au abonament la cel putin 3 numere de telefon.\n");
	printf("4.Creeaza un contract.\n");
	printf("5.Inchideti aplicatia.\n");
	printf("Introduceti numarul optiunii: ");
	scanf("%d", &option);
	printf("\n");
}