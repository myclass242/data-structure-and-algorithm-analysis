#include "exercise3_1.h"
#include <iostream>

void PrintLots(const std::list<int> &li, const std::list<int> &position)
{
    auto begin = li.cbegin();
    auto end = li.cend();

    auto positionBegin = position.cbegin();
    auto positionEnd = position.cend();
    int currentPosition = 0;
    int lastPosition = 0;
    while (begin != end && positionBegin != positionEnd)
    {
        currentPosition = *positionBegin;
        for (int i = 0; i < currentPosition - lastPosition; ++i)
        {
            ++begin;
            if (begin == end)
            {
                std::cout << "Out of range" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cout << "list[" << currentPosition << "] : " << *begin << std::endl;
        lastPosition = currentPosition;
        ++positionBegin;
    }
}