#include "gcd.h"

int EuclideanAlgorithmGCD(int m, int n)
{
	while (n != 0)
	{
		int rem = m % n;
		m = n;
		n = rem;
	}
	return m;
}

int DecreaseTechniqueGCD(int m, int n)
{
	while (n != m)
	{
		if (m < n)
		{
			n -= m;
		}
		else
		{
			m -= n;
		}
	}
	return n;
}