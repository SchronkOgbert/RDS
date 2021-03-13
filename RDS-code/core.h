#ifndef CORE
#define CORE
#include "libs.h"
#define S_ISDIR(m) (((m) & 0170000) == (0040000))

//setup functions
void setup();
int create_dir(char* dir_name);

//utility functions
int gcd(int x, int y);
int scm(int x, int y);
int digit_prod(int x);
int no_digits(int x);

#endif

