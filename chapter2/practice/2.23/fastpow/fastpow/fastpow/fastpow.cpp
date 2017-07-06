#include "fastpow.h"

long long FastPowByloop(long long x, int n)
{
	long long pow = 1;
	while (n)
	{
		if (n == 0)
		{
			break;
		}
		if (n % 2)
		{
			pow *= x;
			x *= x;
			n /= 2;
			
		}
		else
		{
			//pow *= x;
			x *= x;
			n /= 2;
		}
	}
	return pow;
}

long long FastPowByRecursion(long long x, int n)
{
	if (n == 0)
	{
		return 1;
	}

	if (n % 2)
	{
		return x * FastPowByRecursion(x * x, n / 2);
	}
	else
	{
		return FastPowByRecursion(x * x, n / 2);
	}
}
