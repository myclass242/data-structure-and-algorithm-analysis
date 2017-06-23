#include "findmaxlist.h"
#include <iostream>
#include<stdlib.h>

int main(void)
{
	std::vector<int> vi{ -2, 11, -4, 13, -5, -2, -6, 8, 3, 6, 1, 9, 3, -4, 5, 6, -7, 9};
	std::tuple<int, int, int> maxList = FindMaxList(vi);
	std::cout << "The Max LIst is " << std::get<0>(maxList) << " to " << std::get<1>(maxList) << ": ";
	for (int begin = std::get<0>(maxList); begin <= std::get<1>(maxList); ++begin)
	{
		std::cout << vi[begin] << ' ';
	}
	std::cout << std::endl;
	std::cout << "The Max Sum is " << std::get<2>(maxList) << std::endl;
	system("pause");
	return 0;
}