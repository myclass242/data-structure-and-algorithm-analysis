#pragma once
#ifndef FIGURE_3_25_H_
#define FIGURE_3_25_H_
#include <iostream>

template<typename Iterator>
void PrintContainerByRecursion(Iterator begin, Iterator end, std::ostream &out)
{
    if (begin == end)
    {
        return;
    }

    out << *begin++ << std::endl;
    PrintContainerByRecursion(begin, end, out);
}

template<typename Iterator>
void PrintContainerByLoop(Iterator begin, Iterator end, std::ostream &out)
{
    while (begin != end)
    {
        out << *begin++ << std::endl;
    }
}
#endif
