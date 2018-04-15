#include <iostream>
#include "hash.h"
#include "test.h"

int main(void)
{
    std::cout << SimpleStrHash1("Hello World", 11) << ' ' << SimpleStrHash2("Hello World", 11) << std::endl;
    std::cout << GoodStrHash("Hello World", 37) << std::endl;

    TestSeparateChainingHash();
    std::forward_list<int> fl;
    
    return 0;
}
