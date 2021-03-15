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
		char* columns[] = { "Nume", "Prenume", "Adresa", "CNP", "Data emiterii", "Suma" };
		create_csv_file(BILLS, 6, columns);
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
	if (!bills)
	{
		bills = fopen(BILLS, "a");
	}
	for (int i = 0; i < argc - 1; i++)
	{
		fprintf(file, "%s,", argv[i]);
	}
	fprintf(file, "%s\n", argv[argc - 1]);
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
			if (CNP == string_to_long(get_field(buffer, 3)))
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
	char* res = malloc(21);
	char buffer[21] = "";
	while (x)
	{
		buffer[strlen(buffer)] = (x % 10) + '0';
		buffer[strlen(buffer) + 1] = '\0';
		x /= 10;
	}
	_strrev(buffer);
	strcpy(res, buffer);
	return res;
}

char* long_to_string(long x)
{
	char* res = malloc(21);
	char buffer[21] = "";
	while (x)
	{
		buffer[strlen(buffer)] = (x % 10) + '0';
		buffer[strlen(buffer) + 1] = '\0';
		x /= 10;
	}
	_strrev(buffer);
	strcpy(res, buffer);
	return res;
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

char* get_field(char* line, int num)
{
	char buffer[256];
	strcpy(buffer, line);
	char* token = strtok(buffer, ",");
	int i = 0;
	/* walk through other tokens */
	while (token != NULL) {
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
