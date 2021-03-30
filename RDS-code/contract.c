#include "contract.h"
#include "core.h"

void createcontract()
{
	contract option;
	select_service(&option);
	select_type(&option);
	select_years(&option);
}

void select_service(contract *con)
{
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
	printf("Selectati durata abonamentului:\n");
	printf("0.Un an\n");
	printf("1.Doi ani\n");
	scanf("%d", &con->years);
}
