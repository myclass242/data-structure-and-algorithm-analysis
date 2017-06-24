#include "cubesum.h"
#include <iostream>
#include <stdlib.h>
int main(void)
{
	std::cout << 7 << "的立方和是： " << CubeSum(7) << std::endl;
	std::cout << "Fib(10) : " << Fib(10) << std::endl;
	std::cout << "Factorial(50): " << Factorial(10) << std::endl;

	//maxsubsum
	std::vector<int> vi{ -2, 11, -4, 13, -5, -2 };
	std::cout << "MaxSubSum1: " << MaxSubSum1(vi) << std::endl;
	std::cout << "MaxSubSum2: " << MaxSubSum2(vi) << std::endl;
	system("pause");
	return 0;
}