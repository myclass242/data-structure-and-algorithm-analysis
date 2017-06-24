#include "cubesum.h"

int CubeSum(int n)
{
	int middleSum = 0;
	for (int i = 1; i <= n; ++i)
	{
		middleSum += i * i * i;
	}
	return middleSum;
}

long Factorial(int n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return n * Factorial(n - 1);
	}
}

long Fib(int n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return Fib(n - 1) + Fib(n - 2);
	}
}

int MaxSubSum1(const std::vector<int> &a)
{
	int maxSum = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = i; j < a.size(); ++j)
		{
			int thisSum = 0;
			for (int k = i; k <= j; ++k)
			{
				thisSum += a[k];
			}
			if (thisSum > maxSum)
			{
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

int MaxSubSum2(const std::vector<int>& a)
{
	int maxSum = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;
		for (int j = i; j < a.size(); ++j)
		{
			thisSum += a[j];
			if (thisSum > maxSum)
			{
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}
