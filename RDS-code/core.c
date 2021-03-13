#include "core.h"

void setup()
{
	char* folder;
	//folder = "C:\\Users\\SaMaN\\Desktop\\Ppln";
	folder = "db";
	struct stat sb;

	if (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode)) 
	{
		printf("Successfully opened %s directory...\n", folder);				
	}
	else 
	{
		printf("No file directory found, creating directory...\n");
		create_dir(folder);
	}
	if (!check_file("db/abonamente.csv"))
	{
		char* columns[] = { "Nume abonament", "Tip abonament", "Durata abonament", "Cost abonament" };
		create_csv_file("db/abonamente.csv", 4, columns);
		//delete_string_array(4, columns);
	}
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

void delete_string_array(int elc, char* v[])
{
	for (int i = 0; i < elc; i++)
	{
		free(v + i);
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
