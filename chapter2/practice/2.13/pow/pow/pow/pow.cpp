#include "pow.h"

long long PowNormal(int a, int x, int n)
{
	long long thisResult = 1;
	while (n)
	{
		thisResult *= x;
		--n;
	}
	return a * thisResult;
}

static long long PowerBin(int x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	if (n % 2)
	{
		return x * PowerBin(x, n / 2) * PowerBin(x, n / 2);
	}
	else
	{
		return PowerBin(x, n / 2) * PowerBin(x, n / 2);
	}
}

long long PowerBinary(int a, int x, int n)
{
	return a * PowerBin(x, n);
}
