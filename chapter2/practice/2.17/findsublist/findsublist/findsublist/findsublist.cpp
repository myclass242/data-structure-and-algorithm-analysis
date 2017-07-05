#include "findsublist.h"

int FindMinSubList(const std::vector<int>& vi)
{
	int thisMinSum = 0;
	int minSum = vi[0];
	for (const auto &i : vi)
	{
		thisMinSum += i;
		if (thisMinSum < minSum)
		{
			minSum = thisMinSum;
		}
		else
		{
			thisMinSum = 0 > thisMinSum ? thisMinSum : 0;
		}
	}
	return minSum;
}

int FindMinSubListInPlusSubList(const std::vector<int>& vi)
{
	int thisMinSum = 0;
	int minSum = INT_MAX;
	for (const auto &i : vi)
	{
		if (i > 0)
		{
			thisMinSum += i;
		}
		else
		{
			if (thisMinSum > 0)
			{
				if (thisMinSum < minSum)
				{
					minSum = thisMinSum;
				}
			}
			thisMinSum = 0;
		}
	}

	/* 处理正子序列是序列尾部的特许情况 */
	if (thisMinSum < minSum)
	{
		minSum = thisMinSum;
	}
	return minSum;
}

int FindMaxSubListOfProduct(const std::vector<int>& vi)
{
	int thisProduct = 1;
	int maxProduct = 0;
	for (const auto &i : vi)
	{
		thisProduct *= i;
		if (thisProduct == 0)
		{
			thisProduct = 1;
		}
		if (thisProduct > maxProduct)
		{
			maxProduct = thisProduct;
		}
	}
	return maxProduct;
}
