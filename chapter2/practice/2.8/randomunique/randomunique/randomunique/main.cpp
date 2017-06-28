#include "randomunique.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

const long long int ARR_SIZE = 6400000;

int main(void)
{
	int *arr = new int[ARR_SIZE]();
	clock_t start = clock();
	RandomUnique2(arr, ARR_SIZE);
	clock_t finish = clock();
	std::cout << "Time lapse :" << finish - start << std::endl;
	/*for (int i = 0; i < 20; ++i)
	{
		std::cout << *(arr + i) << ' ';
	}
	std::cout << std::endl;*/
	delete[] arr;

	system("pause");
	return 0;
}