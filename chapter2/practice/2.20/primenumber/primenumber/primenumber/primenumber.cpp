#include "primenumber.h"
#include <math.h>

bool IsPrimeNumber(int n)
{
	for (int i = 2; i <= sqrt(n); ++i)
	{
		if (n % 2 == 0)
		{
			return false;
		}
	}
	return true;
}
