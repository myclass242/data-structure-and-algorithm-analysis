#include "cubesum.h"

int CubeSum(int n)
{
	int middleSum = 0;
	for (int i = 1; i <= n; ++i)
	{
		middleSum += i * i * i;
	}
	return middleSum;
}

long Factorial(int n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return n * Factorial(n - 1);
	}
}

long Fib(int n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return Fib(n - 1) + Fib(n - 2);
	}
}

int MaxSubSum1(const std::vector<int> &a)
{
	int maxSum = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = i; j < a.size(); ++j)
		{
			int thisSum = 0;
			for (int k = i; k <= j; ++k)
			{
				thisSum += a[k];
			}
			if (thisSum > maxSum)
			{
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

int MaxSubSum2(const std::vector<int>& a)
{
	int maxSum = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;
		for (int j = i; j < a.size(); ++j)
		{
			thisSum += a[j];
			if (thisSum > maxSum)
			{
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

static int do_maxSumRec(const std::vector<int> &a, int begin, int end)
{
	if ((begin == end) || (begin == end -1))
	{
		if (a[begin] > 0)
		{
			return a[begin];
		}
		else
		{
			return 0;
		}
	}
	int center = (begin + end) / 2;
	int leftMaxSum = do_maxSumRec(a, begin, center);
	int rightMaxSum = do_maxSumRec(a, center, end);

	int leftBorderMaxSum = 0;
	int leftBorderSum = 0;
	for (int i = center - 1; i >= 0; --i)
	{
		leftBorderSum += a[i];
		if (leftBorderSum > leftBorderMaxSum)
		{
			leftBorderMaxSum = leftBorderSum;
		}
	}
	int rightBorderMaxSum = 0;
	int rightBorderSum = 0;
	for (int i = center; i < end; ++i)
	{
		rightBorderSum += a[i];
		if (rightBorderSum > rightBorderMaxSum)
		{
			rightBorderMaxSum = rightBorderSum;
		}
	}
	int maxOfRightAndLeft = leftMaxSum > rightMaxSum ? leftMaxSum : rightMaxSum;
	int BorderMaxSum = leftBorderMaxSum + rightBorderMaxSum;
	return maxOfRightAndLeft > BorderMaxSum ? maxOfRightAndLeft : BorderMaxSum;
}

int MaxSubSum3(const std::vector<int> &a)
{
	return do_maxSumRec(a, 0, a.size());
}

int MaxSubSUm4(const std::vector<int> &a)
{
	int maxSum = 0;
	int thisSum = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		thisSum += a[i];
		if (thisSum > maxSum)
		{
			maxSum = thisSum;
		}
		else if (thisSum < 0)
		{
			thisSum = 0;
		}
	}
	return maxSum;
}