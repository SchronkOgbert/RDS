#include "core.h"

void setup()
{	
	//checks if the folder exists
	check_working_folder();
	//this part checks if the files we're gonna write actually exist
	//if they don't, they get created
	check_files();
	//for speed, this will stay open while the program runs
	get_people();
	bills = fopen(BILLS, "a");
}

int create_dir(char* dir_name)
{
	int check;
	check = mkdir(dir_name);
	if (!check)
	{
		printf("Succesfully created directory %s...\n", dir_name);
		return 1;
	}
	printf("Unable to create directory %s...\n", dir_name);
	exit(-1);
}

int check_file(char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file)
	{
		fclose(file);
		return 1;
	}
	printf("File %s does not exist...\n", filename);
	return 0;
}

void check_files()
{
	if (!check_file(CLIENTS))
	{
		char* columns[] = { "Nume", "Prenume", "CNP" };
		create_csv_file(CLIENTS, 3, columns);
	}
	if (!check_file(TEMPLATES))
	{
		char* columns[] = { "Nume abonament", "Tip abonament", "Durata abonament", "Cost abonament" };
		create_csv_file(TEMPLATES, 4, columns);
		generate_templates();
	}
	if (!check_file(BILLS))
	{
		char* columns[] = { "Nume", "Prenume", "Serviciu", "Adresa", "CNP", "Data emiterii", "Suma" };
		create_csv_file(BILLS, 7, columns);
	}
	if (!check_file(PHONES))
	{
		char* columns[] = { "CNP", "Telefon" };
		create_csv_file(PHONES, 2, columns);
	}
}

void get_people()
{
	FILE* file = fopen(CLIENTS, "r");
	char buffer[256];
	fgets(buffer, 256, file);
	char name[41];
	char first_name[41];
	long cnp;
	while (fgets(buffer, 256, file))
	{
		strcpy(name, get_field(buffer, 0));
		strcpy(first_name, get_field(buffer, 1));
		cnp = string_to_long(get_field(buffer, 2));
		people = realloc(people, sizeof(person) * (people_count + 1));
		people_count++;
		people[people_count - 1] = person_init(name, first_name, cnp);
	}
	fclose(file);
}

void check_working_folder()
{
	struct stat sb;
	if (stat(WORKING_FOLDER, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		printf("Successfully opened %s directory...\n", WORKING_FOLDER);
	}
	else
	{
		printf("No file directory found, creating directory...\n");
		create_dir(WORKING_FOLDER);
		printf("Success!...\n");
	}
}

void create_csv_file(char* filename, int argc, char* argv[])
{
	printf("Creating %s...\n", filename);
	FILE* file = fopen(filename, "w");
	for (int i = 0; i < argc - 1; i++)
	{
		fprintf(file, "%s,", argv[i]);
	}
	fprintf(file, "%s\n", argv[argc - 1]);
	fclose(file);
}

void generate_templates()
{
	FILE* file = fopen(TEMPLATES, "a");
	if (file)
	{
		char buffer[128] = "Basic,Telefon,1,5\n";
		strcat(buffer, "Basic,Telefon,2,5\n");
		strcat(buffer, "Premium,Telefon,1,10\n");
		strcat(buffer, "Premium,Telefon,2,10\n");
		fprintf(file, "%s", buffer);
		strcpy(buffer, "Basic,Televiziune,1,10\n");
		strcat(buffer, "Basic,Televiziune,2,10\n");
		strcat(buffer, "Premium,Televiziune,1,20\n");
		strcat(buffer, "Premium,Televiziune,2,20\n");
		fprintf(file, "%s", buffer);
		fclose(file);
	}
	else
	{
		printf("Failed to create templates, exit...\n");
		system("pause");
		exit(-1);
	}
}

void prepare_quit()
{
	if (return_buffer)
	{
		free(return_buffer);
	}
	if (bills)
	{
		fclose(bills);
	}
	for (int i = 0; i < people_count; i++)
	{
		free(people[i]);
	}
	free(people);
}

void append_to_csv(FILE* file, int argc, char* argv[])
{
	//the cnp should be the fourth el in the array
	if (bills == NULL)
	{
		bills = fopen(BILLS, "a");
	}
	if (bills)
	{
		for (int i = 0; i < argc - 1; i++)
		{
			fprintf(file, "%s,", argv[i]);
		}
		fprintf(file, "%s\n", argv[argc - 1]);
	}
	else
	{
		printf("failed to open file...\n");
	}
}

char* search_bills(long CNP)
{
	FILE* file = fopen(BILLS, "r");
	char buffer[256];
	if (file)
	{
		fgets(buffer, 256, file);
		while (fgets(buffer, 256, file))
		{
			if (CNP == string_to_long(get_field(buffer, 4)))
			{
				if (return_buffer)
				{
					free(return_buffer);					
				}
				return_buffer = malloc(strlen(buffer) + 1);
				strcpy(return_buffer, buffer);
			}
		}
	}
	fclose(file);
	return return_buffer;
}

int check_cnp(long CNP)
{
	for (int i = 0; i < people_count; i++)
	{
		if (people[i]->cnp == CNP)
		{
			return 1;
		}
	}
	return 0;
}

char* int_to_string(int x)
{
	char buffer[21] = "";
	while (x)
	{
		buffer[strlen(buffer)] = (x % 10) + '0';
		buffer[strlen(buffer) + 1] = '\0';
		x /= 10;
	}
	_strrev(buffer);
	if (return_buffer)
	{
		free(return_buffer);
	}
	return_buffer = malloc(strlen(buffer) + 1);
	strcpy(return_buffer, buffer);
	return return_buffer;
}

char* long_to_string(long x)
{
	char buffer[21] = "";
	while (x)
	{
		buffer[strlen(buffer)] = (x % 10) + '0';
		buffer[strlen(buffer) + 1] = '\0';
		x /= 10;
	}
	_strrev(buffer);
	if (return_buffer)
	{
		free(return_buffer);
	}
	return_buffer = malloc(strlen(buffer) + 1);
	strcpy(return_buffer, buffer);
	return return_buffer;
}

long string_to_long(char* string)
{
	long res = 0;
	for (int i = 0; string[i] != '\0' && string[i] != '\n'; i++)
	{
		res = res * 10 + (string[i] - '0');
	}
	return res;
}

void delete_string_array(int elc, char* v[])
{
	for (int i = 0; i < elc; i++)
	{
		if (!v[i])
		{
			printf("Ivalid memory location...\n");
			continue;
		}
		free(v[i]);
	}
}

void set_bill_data(char* bill_lines)
{
	char* tmp = malloc(strlen(bill_lines) + 1);
	char buffer[128];
	free_bill_data();
	strcpy(tmp, bill_lines);
	for (int i = 0; i < strlen(tmp); i++)
	{
		strcpy(buffer, "");
		while (tmp[i] != '\n' && tmp[i]!='\0')
		{
			strapp(buffer, tmp[i]);
			i++;
		}
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		tm.tm_year += 1900;
		tm.tm_mon++;
		struct tm bill_date = parse_date(get_field(buffer, 5));
		if (compare_dates(tm, bill_date, 2))
		{
			bill_count++;
			if (bill_data)
			{
				bill_data = (bill**)realloc(bill_data, sizeof(bill*) * bill_count);
			}
			else
			{
				bill_data = (bill**)malloc(sizeof(bill*) * bill_count);
			}
			char name[40];
			strcpy(name, get_field(buffer, 0));
			char first_name[40];
			strcpy(first_name, get_field(buffer, 1));
			char address[60];
			strcpy(address, get_field(buffer, 3));
			int sum = string_to_long(get_field(buffer, 6));
			long cnp = string_to_long(get_field(buffer, 4));
			service_type type;
			if (strcmp("Telefon", get_field(buffer, 2)) == 0)
			{
				type = Phone;
			}
			else
			{
				type = Cable;
			}
			bill_data[bill_count - 1] = bill_init(name, first_name, address, cnp, type, bill_date, sum);

		}
	}
	free(tmp);
}

struct tm parse_date(char* in_string)
{
	char buffer[16];
	strcpy(buffer, in_string);
	struct tm res;
	int data = 0;
	char* token = strtok(buffer, "/");
	int i = 0;
	/* walk through other tokens */
	while (token != NULL) 
	{
		switch (i)
		{
		case 0:
		{
			res.tm_wday = string_to_long(token);
			break;
		}
		case 1:
		{
			res.tm_mon = string_to_long(token);
			break;
		}
		case 2:
		{
			res.tm_year = string_to_long(token);
			break;
		}
		default:
			return res;
		}
		token = strtok(NULL, "/");
		i++;
	}
	return res;
}

int compare_dates(struct tm d1, struct tm d2, int level)
{
	switch (level)
	{
	case 1:
		return d1.tm_year == d2.tm_year;
	case 2:
		return (d1.tm_year == d2.tm_year && d1.tm_mon == d2.tm_mon);
	default:
		return (d1.tm_year == d2.tm_year && d1.tm_mon == d2.tm_mon && d1.tm_mday == d2.tm_mday);
	}
}

void strapp(char* s, char c)
{
	s[strlen(s) + 1] = '\0';
	s[strlen(s)] = c;	
}

void free_bill_data()
{
	if (bill_data)
	{
		for (int i = 0; i < bill_count; i++)
		{
			if (bill_data[i])
			{
				free(bill_data[i]);
			}
		}
	}
	free(bill_data);
	bill_count = 0;
}

int has_cable(long cnp)
{
	for (int i = 0; i < bill_count; i++)
	{
		if (bill_data[i]->service == Cable)
		{
			return 1;
		}
	}
}

void map_phones()
{
	FILE* file = fopen(PHONES, "r");
	char buffer[256];
	if (file)
	{
		fgets(buffer, 256, file);
		while (fgets(buffer, 256, file))
		{
			long cnp = string_to_long(get_field(buffer, 3));
			int cnp_index = has_phone(cnp);
			if (cnp_index > -1)
			{
				phones[cnp_index]->number++;
			}
			else
			{
				if (phones)
				{
					phone_count++;
					phones = (phone**)realloc(phones, sizeof(phone*) * phone_count);					
				}
				else
				{
					phone_count = 1;
					phones = (phone**)malloc(sizeof(phone*));
				}
				phones[phone_count - 1] = init_phone(cnp, 1);
			}
		}
	}
	fclose(file);
}

int has_phone(long cnp)
{
	for (int i = 0; i < phone_count; i++)
	{
		if (phones[i]->cnp == cnp)
		{
			return i;
		}
	}
	return -1;
}

char* get_field(char* line, int num)
{
	char buffer[256];
	strcpy(buffer, line);
	char* token = strtok(buffer, ",");
	int i = 0;
	/* walk through other tokens */
	while (token != NULL) 
	{
		if (i == num)
		{
			if (return_buffer)
			{
				free(return_buffer);
			}
			return_buffer = malloc(strlen(token) + 1);
			strcpy(return_buffer, token);
			return return_buffer;
		}
		token = strtok(NULL, ",");
		i++;
	}
	return NULL;
}
