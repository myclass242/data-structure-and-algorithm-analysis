#include "gcd.h"
#include <cmath>

int Gcd(int a, int b)
{
	if (a == 1 && b == 1)
	{
		return 1;
	}
	if (a == 0 || b == 0)
	{
		return a + b;
	}

	if (a % 2)
	{
		if (b % 2)
		{
			return Gcd((a + b) / 2, abs(a - b) / 2);
		}
		else
		{
			return Gcd(a, b / 2);
		}
	}
	else
	{
		if (b % 2)
		{
			return Gcd(a / 2, b);
		}
		else
		{
			return 2 * Gcd(a / 2, b / 2);
		}
	}
}
