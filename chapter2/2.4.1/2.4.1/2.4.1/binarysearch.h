#pragma once
#ifndef BINARYSEARCH_H_
#define BINARYSEARCH_H_
#include <vector>

template <typename T>
int FindElementByBinarysearch(const std::vector<T> &a, const T &e)
{
	int low = 0;
	int high = a.size();
	while (low <= high)
	{
		int middle = (low + high) / 2;
		if (a[middle] < e)
		{
			low = middle + 1;
		}
		else if (e < a[middle])
		{
			high = middle - 1;
		}
		else
		{
			return middle;
		}
	}
	return a.size();
}

template <>
int FindElementByBinarysearch(const std::vector<int> &vi, const int &targe)
{
	int low = 0;
	int high = vi.size();
	while (low <= high)
	{
		int middle = (low + high) / 2;
		if (vi[middle] < targe)
		{
			low = middle + 1;
		}
		else if (vi[middle] > targe)
		{
			high = middle - 1;
		}
		else
		{
			return middle;
		}
	}
	return vi.size();
}
#endif