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
#define SUBSCRIPTIONS "db/abonamente_clienti.csv"
#define CONFIG "db/config.ini"

//needed files
FILE* bills;
person** people;
bill** bill_data;
phone** phones;
int people_count;
int bill_count;
int phone_count;

//setup functions
void setup();
void check_working_folder();
void check_files();
void get_people();
int create_dir(char* dir_name);
int check_file(char* filename);
void create_csv_file(char* filename, int argc, char* argv[]);
void generate_templates();
void create_config_file();

void prepare_quit();

//db managing functions
void append_to_csv(FILE* file, int argc, char* argv[]);
char* search_bills(long long CNP);
int check_cnp(long long CNP);
void set_bill_data(char* bill_lines);
char* get_full_csv_line(int number, char* filename);
int does_client_exist(long long cnp);

//utility functions
char* int_to_string(int x);
char* llong_to_string(long long x);
long long string_to_llong(char* string);
char* get_field(char* line, int num);
struct tm parse_date(char* in_string);
int compare_dates(struct tm d1, struct tm d2, int level);
void strapp(char* s, char c);
void free_bill_data();
int has_cable(long long cnp);
void map_phones();
int has_phone(long long cnp);
inline void clear_console() { system("cls"); }
char* get_config_property(char* key);
void print_file_content(char* filename);
void add_person(char* name, char* first_name, long long cnp);
void print_phone_contracts(long long cnp);
char** get_phone_numbers(long long cnp);
struct tm get_date();
char* get_date_string(struct tm date);
void add_phone_to_map(long long cnp);

//low-level stuff functions
void delete_string_array(int elc, char* v[]);

//easter eggs
inline void secret()
{
	clear_console();
	printf("THEN THE WINGED HUSSARS ARRIVED!\n");
}

#endif

