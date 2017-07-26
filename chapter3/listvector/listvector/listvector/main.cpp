#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <string>
#include <forward_list>
#include <stack>
#include <fstream>
#include "zyalg.h"
#include "zyvector.h"
#include "test.h"
#include "usestack.h"

int main(void)
{
	/*TestVector();

	TestList();*/

	//TestForwardList();
	TestStack();

	std::list<int> li{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::forward_list<int> fli{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	std::ifstream inFile;	
	inFile.open("zylist.h", std::ifstream::in);
	if (!inFile.is_open())
	{
		std::cout << "Open File fail" << std::endl;
	}
	else
	{
		BalanceSigned(inFile);
		inFile.close();
	}
	/*std::stack<int> sti;
	sti.top();*/
	system("pause");
	return 0;
}