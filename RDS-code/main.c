#include "core.h"

int main()
{
	setup(); //this function needs to be the first line to be executed
	
	printf("%s", search_bills(123456));
	set_bill_data(search_bills(123456));

	prepare_quit(); //this function needs to be last to be executed

	//system("pause");

	return 0;
}