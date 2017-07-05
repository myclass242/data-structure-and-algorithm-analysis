#include "funcsolution.h"

double SeekContinuousFunctionSolution(const std::function<double(double)> &func, double low, double high)
{
	if (func(low) == 0)
	{
		return low;
	}
	if (func(high) == 0)
	{
		return high;
	}
	double mid = (low + high) / 2;
	if (func(mid) == 0)
	{
		return mid;
	}
	if (func(mid) * func(low) < 0)
	{
		return SeekContinuousFunctionSolution(func, low, mid);
	}
	else if (func(mid) * func(high) < 0)
	{
		return SeekContinuousFunctionSolution(func, mid, high);
	}
}
