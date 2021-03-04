#include "utilities.h"

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

int max(int a, int b)
{
	if (a >= b)
	{
		return a;
	}
	return b;
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
