#include <iostream>
#include <stdlib.h>
#include "funcsolution.h"

int main(void)
{
	std::cout << SeekContinuousFunctionSolution([](double x) {return 3 * x + 2; }, -999999999, 9999999999999999) << std::endl;

	std::cout << SeekContinuousFunctionSolution([](double x) {return (x - 2) * (x - 2) - 1; }, 2, 0) << ' ';
	std::cout << SeekContinuousFunctionSolution([](double x) {return (x - 2) * (x - 2) - 1; }, 2, 5) << std::endl;
	system("pause");
	return 0;
}