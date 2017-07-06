#include "erastothenes.h"
#include <cstdbool>
#include <math.h>

std::vector<int> SearchPrimeNumberByErastothenes(int n)
{
	std::vector<bool> filter(n +1, true);
	std::vector<int> primeNumber;
	for (int i = 2; i < sqrt(n); ++i)
	{
		if (filter[i])
		{
			for (size_t j = 2; i * j < n + 1; ++j)
			{
				filter[i * j] = false;
			}
		}
	}
	for (int i = 2; i < n + 1; ++i)
	{
		if (filter[i])
		{
			primeNumber.push_back(i);
		}
	}
	return primeNumber;
}
