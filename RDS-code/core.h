#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef CORE
#define CORE
#include "libs.h"
#include "objects.h"
#define S_ISDIR(m) (((m) & 0170000) == (0040000))
#define BILLS "db/facturi.csv"
#define TEMPLATES "db/abonamente.csv"
#define WORKING_FOLDER "db"
#define CLIENTS "db/clienti.csv"
#define PHONES "db/telefoane.csv"

//needed files
FILE* bills;
person** people;
bill** bill_data;
int people_count;
int bill_count;
char* return_buffer;

//setup functions
void setup();
void check_working_folder();
void check_files();
void get_people();
int create_dir(char* dir_name);
int check_file(char* filename);
void create_csv_file(char* filename, int argc, char* argv[]);
void generate_templates();

void prepare_quit();

//db managing functions
void append_to_csv(FILE* file, int argc, char* argv[]);
char* search_bills(long CNP);
int check_cnp(long CNP);
void set_bill_data(char* bill_lines);

//utility functions
char* int_to_string(int x);
char* long_to_string(long x);
long string_to_long(char* string);
char* get_field(char* line, int num);
struct tm parse_date(char* in_string);
int compare_dates(struct tm d1, struct tm d2, int level);
void strapp(char* s, char c);
void free_bill_data();
int has_cable(long cnp);

//low-level stuff functions
void delete_string_array(int elc, char* v[]);

#endif

