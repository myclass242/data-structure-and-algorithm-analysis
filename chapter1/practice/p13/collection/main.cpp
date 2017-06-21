#include"collect.h"
#include <iostream>

int main()
{
    Collection<int> ci;
    std::cout << ci.IsEmpty() << std::endl;
    for (int i = 0; i < SIZE; ++i)
    {
        ci.Insert(i , i);
    }
    std::cout << ci.FindMax() << ' ' << ci.FindMin() << std::endl;
    ci.Remove(999);
    std::cout << ci.FindMax() << ' ' << ci.FindMin() << std::endl;
    std::cout << ci.IsEmpty() << std::endl;
    ci.MakeEmpty();
    std::cout << ci.IsEmpty() << std::endl;
    return 0;
}
