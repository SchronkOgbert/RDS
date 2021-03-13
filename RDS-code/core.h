#ifndef CORE
#define CORE
#include "libs.h"
#define S_ISDIR(m) (((m) & 0170000) == (0040000))
#define BILLS "db/facturi.csv"
#define SUBSCRIPTIONS "db/abonamente.csv"
#define WORKING_FOLDER "db"

//needed files
FILE* subscriptions;
FILE* bills;

//setup functions
void setup();
int create_dir(char* dir_name);
int check_file(char* filename);
void create_csv_file(char* filename, int argc, char* argv[]);

void prepare_quit();

//db managing functions
void append_to_csv(FILE* file, int argc, char* argv[]);

//utility functions
int gcd(int x, int y);
int scm(int x, int y);
int digit_prod(int x);
int no_digits(int x);
char* int_to_string(int x);
char* long_to_string(long x);
long string_to_long(char* string);

//low-level stuff functions
void delete_string_array(int elc, char* v[]);

#endif

