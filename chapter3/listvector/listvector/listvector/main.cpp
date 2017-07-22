#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <string>
#include <forward_list>
#include <stack>
#include "zyalg.h"
#include "zyvector.h"
#include "test.h"

int main(void)
{
	/*TestVector();

	TestList();*/

	//TestForwardList();
	TestStack();

	std::list<int> li{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::forward_list<int> fli{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	
	/*std::stack<int> sti;
	sti.top();*/
	system("pause");
	return 0;
}