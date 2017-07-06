#include <iostream>
#include <stdlib.h>
#include <vector>
#include "erastothenes.h"

int main(void)
{
	std::vector<int> primeNumber = SearchPrimeNumberByErastothenes(21200);
	for (const auto &i : primeNumber)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}