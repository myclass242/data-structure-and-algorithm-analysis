#include "findmaxlist.h"
#include <numeric>

std::tuple<int, int, int> FindMaxList(const std::vector<int> &vi)
{
	std::tuple<int, int, int> targetStore;
	for (int i = 0; i < vi.size(); ++i)
	{
		if (vi[i] > 0)
		{
			for (int n = i; n < vi.size(); ++n)
			{
				/* accumulate 算法使用iterator,不能使用下标值。计算范围是[begin,end)的半闭半开区间。如果begin == end，不做和运算*/
				auto sum = std::accumulate(vi.cbegin() + i, vi.cbegin() + n + 1, 0);
				if (sum > std::get<2>(targetStore))
				{
					targetStore = { i, n, sum };
				}
				if (sum <= 0)
				{
					break;
				}
			}
		}
	}
	return targetStore;
}