#include "binarysearch.h"

int FindIn(int * arr, int size, int element)
{
	int begin = 0;
	int end = size;
	int mid = (begin + end) / 2;
	while (begin != end)
	{
		if (arr[mid] < element)
		{
			begin = mid + 1;
		}
		else if (arr[mid] > element)
		{
			end = mid - 1;
		}
		else
		{
			return mid;
		}
		mid = (begin + end) / 2;
	}
	return -1;
}
