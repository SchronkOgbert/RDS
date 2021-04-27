#include "core.h"


void setup()
{	
	//checks if the folder exists
	check_working_folder();
	//this part checks if the files we're gonna write actually exist
	//if they don't, they get created
	check_files();
	map_phones();
	//for speed, this will stay open while the program runs
	get_people();
	//bills = fopen(BILLS, "a");
}

int create_dir(char* dir_name)
{
	int check;
	check = mkdir(dir_name);
	if (!check)
	{
		//printf("Succesfully created directory %s...\n", dir_name);
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
	//printf("File %s does not exist...\n", filename);
	//fclose(file);
	return 0;
}

void check_files()
{
	if (!check_file(CLIENTS))
	{
		char* columns[] = { "Nume", "Prenume", "CNP", "Adresa" };
		create_csv_file(CLIENTS, 4, columns);
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
	if (!check_file(SUBSCRIPTIONS))
	{
		char* columns[] = { "CNP", "Index abonament" };
		create_csv_file(SUBSCRIPTIONS, 2, columns);
	}
	if (!check_file(CONFIG))
	{
		create_config_file();
	}
}

void get_people()
{
	FILE* file = fopen(CLIENTS, "r");
	char buffer[256];
	fgets(buffer, 256, file);
	char name[41];
	char first_name[41];
	long long cnp;
	while (fgets(buffer, 256, file))
	{
		char* tmp = get_field(buffer, 0);
		strcpy(name, tmp);
		if (tmp)
		{
			free(tmp);
		}
		tmp = get_field(buffer, 1);		
		strcpy(first_name, tmp);
		if (tmp)
		{
			free(tmp);
		}
		tmp = get_field(buffer, 2);
		cnp = string_to_llong(tmp);
		if (tmp)
		{
			free(tmp);
		}
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
		//printf("Successfully opened %s directory...\n", WORKING_FOLDER);
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
	//printf("Creating %s...\n", filename);
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

void create_config_file()
{
	FILE* file = fopen(CONFIG, "w");
	fprintf(file, "current_number:70000001");
	fclose(file);
}

void prepare_quit()
{
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

void append_to_csv(char* filename, int argc, char* argv[])
{
	//the cnp should be the fourth el in the array
	FILE* file = fopen(filename, "a");
	if (file)
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
	fclose(file);
}

char* search_bills(long long CNP)
{
	FILE* file = fopen(BILLS, "r");
	char* r = NULL;
	char buffer[256];
	if (file)
	{
		fgets(buffer, 256, file);
		while (fgets(buffer, 256, file))
		{
			char* tmp = get_field(buffer, 4);
			if (CNP == string_to_llong(tmp))
			{
				if (r)
				{
					r = (char*)realloc(r, strlen(r) + strlen(buffer) + 2);
					strcat(r, buffer);
				}
				else
				{
					r = malloc(strlen(buffer) + 1);
					strcpy(r, buffer);
				}				
			}
			if (tmp)
			{
				free(tmp);
			}
		}
	}
	fclose(file);
	return r;
}

int check_cnp(long long CNP)
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
	char* r = malloc(strlen(buffer) + 1);
	strcpy(r, buffer);
	return r;
}

char* llong_to_string(long long x)
{
	char buffer[21] = "";
	while (x)
	{
		buffer[strlen(buffer)] = (x % 10) + '0';
		buffer[strlen(buffer) + 1] = '\0';
		x /= 10;
	}
	_strrev(buffer);
	char* r = malloc(strlen(buffer) + 1);
	strcpy(r, buffer);
	return r;
}

long long string_to_llong(char* string)
{
	long long res = 0;
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
		v[i] = NULL;
	}
}

void set_bill_data(char* bill_lines)
{
	if (bill_lines == NULL || !strcmp(bill_lines, "\n"))
	{
		printf("Nu exista date pentru clientul cautat...\n\n");
		return;
	}
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
		char* ret_val = get_field(buffer, 5);
		struct tm bill_date = parse_date(ret_val);
		if (ret_val)
		{
			free(ret_val);
		}
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
			ret_val = get_field(buffer, 0);
			strcpy(name, ret_val);
			free(ret_val);
			char first_name[40];
			ret_val = get_field(buffer, 1);
			strcpy(first_name, ret_val);
			free(ret_val);
			char address[60];
			ret_val = get_field(buffer, 3);
			strcpy(address, ret_val);
			free(ret_val);
			ret_val = get_field(buffer, 6);
			int sum = string_to_llong(ret_val);
			free(ret_val);
			ret_val = get_field(buffer, 4);
			long long cnp = string_to_llong(ret_val);
			free(ret_val);
			service_type type;
			ret_val = get_field(buffer, 2);
			if (strcmp("Telefon", ret_val) == 0)
			{
				type = Phone;
			}
			else
			{
				type = Cable;
			}
			free(ret_val);
			bill_data[bill_count - 1] = bill_init(name, first_name, address, cnp, type, bill_date, sum);

		}
	}
	free(tmp);
}

char* get_full_csv_line(int number, char* filename)
{
	char* r = NULL;
	char buffer[256];
	FILE* file = fopen(filename, "r");
	//fgets(buffer, 255, file);
	int count = 0;
	do
	{
		count++;
	} while (fgets(buffer, 255, file) && count <= number);
	if (count == number + 1)
	{
		r = (char*)malloc(strlen(buffer) + 1);
		strcpy(r, buffer);
		return r;
	}
	return NULL;
}

int does_client_exist(long long cnp)
{
	FILE* file = fopen(CLIENTS, "r");
	char* buffer[256];
	fgets(buffer, 255, file);
	while (fgets(buffer, 255, file))
	{
		char* tmp = get_field(buffer, 2);
		if (cnp == string_to_llong(tmp))
		{
			free(tmp);
			return 1;
		}
		free(tmp);
	}
	return 0;
}

struct tm parse_date(char* in_string)
{
	char buffer[16];
	if (!in_string)
	{
		printf("Error: Input string is empty");
		return;
	}
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
			res.tm_wday = string_to_llong(token);
			break;
		}
		case 1:
		{
			res.tm_mon = string_to_llong(token);
			break;
		}
		case 2:
		{
			res.tm_year = string_to_llong(token);
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
	bill_data = NULL;
	bill_count = 0;
}

int has_cable(long long cnp)
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
			char* tmp = get_field(buffer, 0);
			long long cnp = string_to_llong(tmp);
			free(tmp);
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

int has_phone(long long cnp)
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

char* get_config_property(char* key)
{
	FILE* conf = fopen(CONFIG, "r");
	char buffer[64];
	while (fgets(buffer, 127, conf))
	{
		char* tmp = _strdup(buffer);
		char* local_key = strtok(buffer, ":");
		if (strcmp(key, local_key) == 0)
		{
			fclose(conf);
			return tmp + strlen(local_key) + 1;
		}
	}
	fclose(conf);
	return NULL;
}

void add_person(char* name, char* first_name, long long cnp)
{
	if (people)
	{
		people_count++;
		people = (person**)realloc(people, sizeof(person*) * people_count);
		people[people_count - 1] = person_init(name, first_name, cnp);
	}
	else
	{
		people_count = 1;
		people = (person**)malloc(sizeof(person*));
		people[people_count - 1] = person_init(name, first_name, cnp);
	}
}

void print_phone_contracts(long long cnp)
{
	FILE* file = fopen(SUBSCRIPTIONS, "r");
	char buffer[128];
	char* res = NULL;
	fgets(buffer, 127, file);
	int i = 0;
	char** numbers = get_phone_numbers(cnp);
	if (numbers) {
		while (fgets(buffer, 127, file))
		{
			char* tmp = get_field(buffer, 0);
			char* type = get_field(buffer, 1);
			int t = string_to_llong(type);
			free(type);
			if (cnp == string_to_llong(tmp) && t / 5 == 0)
			{
				free(tmp);
				tmp = get_field(buffer, 1);
				int index = string_to_llong(tmp);
				free(tmp);
				tmp = get_full_csv_line(t, TEMPLATES);
				printf("%sNumar de telefon: %s", tmp, numbers[i]);
				free(numbers[i]);
				i++;
				free(tmp);
			}
		}
	}
	else
		printf("Nu s-au gasit numere de telefon pentru acest client.\n");
	free(numbers);
	fclose(file);
}

char** get_phone_numbers(long long cnp)
{
	char** numbers = NULL;
	int i = 0;
	FILE* file = fopen(PHONES, "r");
	char buffer[128];
	fgets(buffer, 127, file);
	while (fgets(buffer, 127, file))
	{
		char* tmp = get_field(buffer, 0);
		if (cnp == string_to_llong(tmp))
		{
			free(tmp);
			if (i)
			{
				i++;
				numbers = (char**)realloc(numbers, sizeof(char*) * i);
			}
			else
			{
				i++;
				numbers = (char**)malloc(sizeof(char*) * i);
			}
			tmp = get_field(buffer, 1);
			numbers[i - 1] = _strdup(tmp);
			free(tmp);
		}
	}
	return numbers;
}

struct tm get_date()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	tm.tm_year += 1900;
	tm.tm_mon++;
	return tm;
}

char* get_date_string(struct tm date)
{
	char* res = malloc(11);
	strcpy(res, "");
	if (date.tm_mday < 10)
	{
		strcat(res, "0");
	}	
	char* tmp = int_to_string(date.tm_mday);
	strcat(res, tmp);
	free(tmp);
	strcat(res, "/");
	if (date.tm_mon < 10)
	{
		strcat(res, "0");
	}
	tmp = int_to_string(date.tm_mon);
	strcat(res, tmp);
	free(tmp);
	strcat(res, "/");
	tmp = int_to_string(date.tm_year);
	strcat(res, tmp);
	free(tmp);
	return res;
}

char* get_field(char* line, int num)
{
	char buffer[256];
	strcpy(buffer, line);
	char* token = strtok(buffer, ",");
	char* r = NULL;
	int i = 0;
	/* walk through other tokens */
	while (token != NULL) 
	{
		if (i == num)
		{
			/**if (return_buffer)
			{
				free(return_buffer);
			}
			return_buffer = malloc(strlen(token) + 1);*/
			//strcpy(return_buffer, token);
			r = malloc(strlen(token) + 1);
			strcpy(r, token);
			return r;
		}
		token = strtok(NULL, ",");
		i++;
	}
	return NULL;
}

void print_file_content(char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file)
	{
		char buffer[256];
		fgets(buffer, 255, file);
		while (fgets(buffer, 255, file))
		{
			printf("%s", buffer);
		}
		fclose(file);
	}
	else
	{
		printf("Nu exista fisierul solicitat\n");
	}
}

void add_phone_to_map(long long cnp)
{
	int found = 0;
	for (int i = 0; i < phone_count; i++)
	{
		found = (phones[i]->cnp == cnp);		
		if (found)
		{
			phones[i]->number++;
			break;
		}
	}
	if (!found)
	{
		phones = (phone**)realloc(phones, sizeof(phone*) * ++phone_count);
		phones[phone_count - 1] = init_phone(cnp, 1);
	}
}
