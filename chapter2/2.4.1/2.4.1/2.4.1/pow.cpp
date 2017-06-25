#include "pow.h"

long long pow(long long x, long long n)
{
	if (n == 0)
	{
		return 1;
	}
	if (n % 2)
	{
		return x * pow(x * x, n / 2);
	}
	else
	{
		return pow(x * x, n / 2);
	}
}
