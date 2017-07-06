#include <iostream>
#include <stdlib.h>
#include "fastpow.h"

int main(void)
{
	long long pow = FastPowByloop(2, 7);
	std::cout << pow << std::endl;
	pow = FastPowByRecursion(2, 7);
	std::cout << pow << std::endl;

	system("pause");
	return 0;
}