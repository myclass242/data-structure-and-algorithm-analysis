#include <iostream>
#include <random>
#include <stdlib.h>
#include "findsublist.h"

int main(void)
{
	std::default_random_engine e;
	std::uniform_int_distribution<int> r(-20, 30);
	std::vector<int> vi;
	for (int i = 0; i < 20; ++i)
	{
		vi.push_back(r(e));
	}
	for (const auto &i : vi)
	{
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	
	std::cout << "��С�����к�" << std::endl;
	std::cout << FindMinSubList(vi) << std::endl;

	std::cout << "��С�������к�" << std::endl;
	std::cout << FindMinSubListInPlusSubList(vi) << std::endl;

	std::cout << "��������г˻�" << std::endl;
	std::cout << FindMaxSubListOfProduct(vi) << std::endl;

	system("pause");
	return 0;
}