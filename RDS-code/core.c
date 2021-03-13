#include "core.h"

void setup()
{
	const char* folder;
	//folder = "C:\\Users\\SaMaN\\Desktop\\Ppln";
	folder = "/db";
	struct stat sb;

	if (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode)) 
	{
		printf("Successfully opened %s directory...\n", folder);
		return;
	}
	else 
	{
		printf("No file directory found, creating directory...\n");
		create_dir(folder + 1);
	}
}

int create_dir(char* dir_name)
{
	int check;
	check = mkdir(dir_name, 0777);
	if (!check)
	{
		printf("Succesfully created directory %s...\n", dir_name);
		return 1;
	}
	printf("Unable to create directory %s...\n", dir_name);
	exit(-1);
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
