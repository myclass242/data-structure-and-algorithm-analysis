#include "cubesum.h"
#include "findmaxlist.h"
#include "binarysearch.h"
#include "gcd.h"
#include "pow.h"
#include <iostream>
#include<algorithm>
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
	std::cout << "MaxSubSum3: " << MaxSubSum3(vi) << std::endl;

	auto tuple1 = FindMaxList(vi);
	auto tuple2 = FindMaxList2(vi);
	std::cout << "Max list: " << std::get<0>(tuple1) << " to " << std::get<1>(tuple1) << " max sum is " << std::get<2>(tuple1) << std::endl;
	std::cout << "Max list: " << std::get<0>(tuple2) << " to " << std::get<1>(tuple2) << " max sum is " << std::get<2>(tuple2) << std::endl;
	
	//binarysearch
	std::sort(std::begin(vi), std::end(vi));
	std::cout << FindElementByBinarysearch(vi, 13) << std::endl;

	//gcd
	std::cout << EuclideanAlgorithmGCD(1590, 1989) << ' ' << DecreaseTechniqueGCD(1989, 1590) << std::endl;

	//pow
	std::cout << "3^4=" << pow(3, 4) << std::endl;

	system("pause");
	return 0;
}