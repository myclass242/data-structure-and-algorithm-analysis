#include "findmaxlist.h"
#include <numeric>

std::tuple<int, int, int> FindMaxList(const std::vector<int> &vi)
{
	std::tuple<int, int, int> targetStore;
	for (int i = 0; i < vi.size(); ++i)
	{
		if (vi[i] > 0)
		{
			std::tuple<int, int, int> thisSum{};
			for (int n = i; n < vi.size(); ++n)
			{
				/* accumulate �㷨ʹ��iterator,����ʹ���±�ֵ�����㷶Χ��[begin,end)�İ�հ뿪���䡣���begin == end������������*/
				//auto sum = std::accumulate(vi.cbegin() + i, vi.cbegin() + n + 1, 0);
				std::get<2>(thisSum) += vi[n];
				if (std::get<2>(thisSum) > std::get<2>(targetStore))
				{
					targetStore = { i, n, std::get<2>(thisSum) };
				}
				if (std::get<2>(thisSum) <= 0)
				{
					break;
				}
			}
		}
	}
	return targetStore;
}