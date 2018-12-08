#pragma once
#ifndef TEST_H_
#define TEST_H_

#include <vector>
#include <functional>
#include <iostream>

template <typename Comparable>
bool TestNormalSort(std::function<void(std::vector<Comparable>)> f,
    std::vector<Comparable> &a)
{
    f(a);
    for (const auto & i : a)
    {
        std::cout << i;
    }
    std::cout << std::endl;
}

#endif
