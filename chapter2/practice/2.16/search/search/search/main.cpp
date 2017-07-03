#include <iostream>
#include <stdlib.h>
#include "binarysearch.h"

int main(void)
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::cout << FindIn(arr, sizeof(arr) / sizeof(arr[0]), 11) << std::endl;

	system("pause");
	return 0;
}