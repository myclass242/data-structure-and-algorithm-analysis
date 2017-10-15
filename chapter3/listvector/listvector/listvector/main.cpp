#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <forward_list>
#include <stack>
#include <fstream>
#include <queue>
#include "zyalg.h"
#include "zyvector.h"
#include "test.h"
#include "usestack.h"
#include "figure3_25.h"


int main(void)
{
	/*TestVector();

	TestList();*/

	//TestForwardList();
	//TestStack();

	//TestBalanceSigned();
	
	//TestPostfixNotation();
    //std::vector<double> dv;
    //dv.resize(2000000, 3.1415966);
    //PrintContainerByLoop(dv.cbegin(), dv.cend(), std::cout);
   // PrintContainerByRecursion(dv.cbegin(), dv.cend(), std::cout);
    
    //TestQueue();

    //TestExercise3_1();
    //TestExercise3_3();
    //TestExercise3_4();
    //TestExercise3_5();
    //TestExercise3_6();
    TestSelfAdjustList();

    
	system("pause");
	return 0;
}