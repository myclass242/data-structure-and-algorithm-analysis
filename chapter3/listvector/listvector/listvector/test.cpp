#include "test.h"
#include <iostream>
#include <string>
#include <fstream>
#include "zyalg.h"
#include "zyvector.h"
#include "zylist.h"
#include "zyforwardlist.h"
#include "zystack.h"
#include "usestack.h"
#include "postfixnotation.h"
#include "zyqueue.h"
#include "exercise3_1.h"
#include "exercise3_3.h"
#include "exercise3_4.h"
#include "exercise3_5.h"
#include "exercise3_6.h"
#include "selfadjustlist.h"

void TestVector(void)
{
	std::cout << "*****zyvector<int>****************" << std::endl;
	zy::zyvector<int> zvii{ 1, 2, 3, 4, 5 , 6, 7, 8, 9, 0 };
	zy::zyvector<int> zvi;
	//std::vector<int> vi{ 1,2,3,4,5,6,7,8,9,0 };
	//show({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 });
	zy::Print(zvi, std::cout);
	std::cout << "size: " << zvi.size() << std::endl;
	std::cout << "capacity: " << zvi.capacity() << std::endl;

	zvi.push_back(11);
	zy::Print(zvi, std::cout);
	std::cout << "size: " << zvi.size() << std::endl;
	std::cout << "capacity: " << zvi.capacity() << std::endl;

	zvi.pop_back();
	zy::Print(zvi, std::cout);
	std::cout << "size: " << zvi.size() << std::endl;
	std::cout << "capacity: " << zvi.capacity() << std::endl;

	zvi.resize(50);
	zy::Print(zvi, std::cout);
	std::cout << "size: " << zvi.size() << std::endl;
	std::cout << "capacity: " << zvi.capacity() << std::endl;

	zvi.resize(12);
	zy::Print(zvi, std::cout);
	std::cout << "size: " << zvi.size() << std::endl;
	std::cout << "capacity: " << zvi.capacity() << std::endl;

	zvi.reserve(200);
	zy::Print(zvi, std::cout);
	std::cout << "size: " << zvi.size() << std::endl;
	std::cout << "capacity: " << zvi.capacity() << std::endl;

	zvi.reserve(2);
	zy::Print(zvi, std::cout);
	std::cout << "size: " << zvi.size() << std::endl;
	std::cout << "capacity: " << zvi.capacity() << std::endl;
	std::cout << "*****zyvector<int>****************" << std::endl;

	std::cout << "*****zyvector<std::string>****************" << std::endl;

	zy::zyvector<std::string> zvstr = { "zhang", "ying", "data", "structures" };
	zy::Print(zvstr, std::cout);
	std::cout << "size: " << zvstr.size() << std::endl;
	std::cout << "capacity: " << zvstr.capacity() << std::endl;

	zy::zyvector<std::string> zvs(std::move(zvstr));
	zy::Print(zvs, std::cout);
	std::cout << "size: " << zvs.size() << std::endl;
	std::cout << "capacity: " << zvs.capacity() << std::endl;

	std::cout << zvs[1] << std::endl;

	std::cout << "*****zyvector<std::string>****************" << std::endl;
}

void TestList(void)
{
	std::cout << "************zy::list<int>**********************" << std::endl;
	zy::list<int> li1;
	zy::list<int> li2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0 };
	auto li3 = li2;
	zy::Print(li3, std::cout);
	zy::Print(li2, std::cout);
	auto begin = li2.begin();
	li2.insert(begin, 0);
	//li2.insert(li2.begin(), 0);
	zy::Print(li2, std::cout);
	li3 = li2;
	zy::Print(li3, std::cout);
	li3 = li3;
	std::cout << "After 赋值" << std::endl;
	zy::Print(li3, std::cout);
	std::cout << "************zy::list<int>**********************" << std::endl;
}

void TestForwardList(void)
{
	std::cout << "***********************zy::forward<int>***********************" << std::endl;
	zy::ForwardList<int> fli1;
	zy::ForwardList<int> fli2{ 1, 2, 3, 4, 5 , 6, 7, 8, 9, 0 };
	auto fli3 = fli2;
	zy::Print(fli3, std::cout);
	fli2.pushFront(-1);
	zy::Print(fli2, std::cout);
	fli3.popFront();
	zy::Print(fli3, std::cout);
	std::cout << "***********************zy::forward<int>***********************" << std::endl;
}

void TestStack(void)
{
	std::cout << "********************************zy::stack<int>*****************************" << std::endl;
	zy::stack<int> st1;
	zy::stack<int> st2{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::cout << st2.top() << std::endl;
	std::cout << "********************************zy::stack<int>*****************************" << std::endl;
}

void TestBalanceSigned(void)
{
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
}

void TestPostfixNotation(void)
{
	std::string str;
	std::cout << "Please enter a center notation:";
	std::cin >> str;
	std::cout << std::endl;
	std::cout << "result is: " << PostfixNotation(str) << std::endl;
}

void TestQueue(void)
{

#ifdef IMPLE_BY_ARRAY
    zy::queue<int, 200> qi{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << "CAPACITY : " << qi.capacity() << std::endl;
#else
    zy::queue<int> qi{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
#endif

    std::cout << "*****************************************************" << std::endl;
    std::cout << "SIZE : " << qi.size() << "  EMPTY : " << qi.isEmpty() << std::endl;
    std::cout << "BACK : " << qi.back() << "  FRONT : " << qi.front() << std::endl;
    std::cout << "*****************************************************" << std::endl;
    qi.push(10);
    std::cout << "SIZE : " << qi.size() << "  EMPTY : " << qi.isEmpty() << std::endl;
    std::cout << "BACK : " << qi.back() << "  FRONT : " << qi.front() << std::endl;
    std::cout << "*****************************************************" << std::endl;
    qi.pop();
    std::cout << "SIZE : " << qi.size() << "  EMPTY : " << qi.isEmpty() << std::endl;
    std::cout << "BACK : " << qi.back() << "  FRONT : " << qi.front() << std::endl;
    std::cout << "*****************************************************" << std::endl;

    for (int i = 0; i < 80; ++i)
    {
        qi.push(i);
        std::cout << "SIZE : " << qi.size() << "  EMPTY : " << qi.isEmpty() << std::endl;
        std::cout << "BACK : " << qi.back() << "  FRONT : " << qi.front() << std::endl;
    }
}

void TestExercise3_1(void)
{
    std::list<int> sour{ 0, 1, 2, 3, 4, 5, 6, 7 };
    std::list<int> position{ 1, 2, 4, 6 };
    PrintLots(sour, position);
}

void TestExercise3_3(void)
{
    zy::list<int> li{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto pos = zy::Find(li.begin(), li.end(), 7);
    std::cout << *pos << std::endl;
}

void TestExercise3_4(void)
{
    zy::list<int> li1{ 1, 3, 5, 7, 9, 11, 13, 15};
    zy::list<int> li2{ 10, 11, 12, 13, 14, 15};
    zy::list<int> intersectionLst = zy::Intersection(li1, li2);
    zy::Print(intersectionLst, std::cout);
}

void TestExercise3_5(void)
{
    zy::list<int> li1{ 1, 3, 5, 7, 9, 11, 13, 15 };
    zy::list<int> li2{ 10, 11, 12, 13, 14, 15 };
    zy::list<int> unionsetLst = zy::Unionset(li1, li2);
    zy::Print(unionsetLst, std::cout);
}

void TestExercise3_6(void)
{
    int step = 0;
    int numbers = 0;
    std::cout << "输入步长和人数:";
    std::cin >> step >> numbers;
    PesephosProblem(step, numbers);
}

void TestSelfAdjustList(void)
{
    zy::SelfAdjustList<int> saL{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    zy::Print(saL, std::cout);
    saL.find(5);
    zy::Print(saL, std::cout);
    auto saLBegin = saL.begin();
    ++saLBegin;
    saL.insert(saLBegin, 11);
    std::cout << *saLBegin << std::endl;
    zy::Print(saL, std::cout);
    {
        zy::SelfAdjustList<int> saL2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    }
}
