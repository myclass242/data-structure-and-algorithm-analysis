#include <iostream>
#include <stdlib.h>
#include "pow.h"

int main(void)
{
	std::cout << PowNormal(1, 4, 16) << std::endl;
	std::cout << PowerBinary(1, 4, 16) << std::endl;

	system("pause");
	return 0;
}