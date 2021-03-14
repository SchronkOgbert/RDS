#ifndef CORE
#define CORE
#include "libs.h"
#define S_ISDIR(m) (((m) & 0170000) == (0040000))
#define BILLS "db/facturi.csv"
#define TEMPLATES "db/abonamente.csv"
#define WORKING_FOLDER "db"
#define CLIENTS "db/clienti.csv"

//needed files
FILE* bills;

//setup functions
void setup();
void check_working_folder();
void check_files();
int create_dir(char* dir_name);
int check_file(char* filename);
void create_csv_file(char* filename, int argc, char* argv[]);
void generate_templates();

void prepare_quit();

//db managing functions
void append_to_csv(FILE* file, int argc, char* argv[]);
char* search_bills(long CNP);
int check_cnp(long CNP);

//utility functions
char* int_to_string(int x);
char* long_to_string(long x);
long string_to_long(char* string);
char* getfield(char* line, int num);

//low-level stuff functions
void delete_string_array(int elc, char* v[]);

#endif

