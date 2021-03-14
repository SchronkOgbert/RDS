#include "core.h"

void setup()
{	
	{
		//this block checks if the working folder exists
		//...should have placed it in a function
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
	//this part checks if the files we're gonna write actually exist
	//if they don't, they get created
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
	return 0;
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
	if (bills)
	{
		fclose(bills);
	}
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
	return NULL;
}

int check_cnp(long CNP)
{
	FILE* file = fopen(BILLS, "r");
	if (file)
	{
		char buffer[256];
		fgets(buffer, 256, file);
		while (fgets(buffer, 256, file))
		{
			char* tmp = _strdup(buffer);
			if (CNP == string_to_long(getfield(buffer, 3)))
			{
				return 1;
			}
			free(tmp);
		}
	}
	return 0;
}

int gcd(int x, int y)
{
	int r;
	while (y)
	{
		r = x % y;
		x = y;
		y = r;
	}
	return x;
}

int scm(int x, int y)
{
	return (x * y) / gcd(x, y);
}

int no_digits(int x)
{
	int res = 0;
	while (x)
	{
		res++;
		x /= 10;
	}
	return res;
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
	for (int i = 0; string[i] != '\0'; i++)
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

int digit_prod(unsigned x)
{
	unsigned res = 1;
	while (x)
	{
		res *= (x % 10);
		x /= 10;
	}
	return res;
}

char* getfield(char* line, int num)
{
	char* token = strtok(line, ",");
	int i = 0;
	/* walk through other tokens */
	while (token != NULL) {
		if (i == 3)
		{
			return token;
		}
		token = strtok(NULL, ",");
		i++;
	}
	return NULL;
}
