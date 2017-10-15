#include "exercise3_6.h"
#include <vector>
#include <iostream>

static void FindNext(std::vector<int>::iterator &potatoPos, std::vector<int> &circle)
{
    do
    {
        ++potatoPos;
        if (potatoPos == circle.end())
        {
            potatoPos = circle.begin();
        }
    } while (0 == *potatoPos);
}

static void MoveStep(std::vector<int>::iterator &potatoPos, int step, std::vector<int> &circle)
{
    while (step)
    {
        FindNext(potatoPos, circle);
        --step;
    }
}

void PesephosProblem(int step, const int numbers)
{
    std::vector<int> circle(numbers, 1);
    int remainPersons = numbers;
    std::vector<int>::iterator potatoPos = circle.begin();
    std::cout << std::endl;
    std::cout << "eliminate: ";
    while (1 < remainPersons)
    {
        MoveStep(potatoPos, step, circle);
        --remainPersons;
        *potatoPos = 0;
        std::cout << potatoPos - circle.begin() + 1 << "  ";
        FindNext(potatoPos, circle);
    }
    std::cout << std::endl;
    std::cout << "remain : " << potatoPos - circle.begin() + 1 << std::endl;
}
