#pragma once
#ifndef SORTING_H_
#define SORTING_H_

#include <vector>
#include <utility>

template <typename Comparable>
void InsertSort(std::vector<Comparable> &a)
{
    for (int i = 1; i < a.size(); ++i)
    {
        Comparable key = std::move(a[i]);
        int j = i;
        for (; j > 0 && key < a[j - 1]; --j)
        {
            a[j] = std::move(a[j - 1]);
        }
        a[j] = std::move(key);
    }
}

template <typename Iterator, typename Comparator = std::less>
void InsertSort(Iterator begin, Iterator end, Comparator com = Comparator<decltype(*begin)>)
{
    if (begin == end)
    {
        return;
    }
    Iterator j;
    for (Iterator i = begin + 1; i != end; ++i)
    {
        auto key = std::move(*i);
        for (j = i; j != begin && com(key, *(j - 1)); --j)
        {
            *j = std::move(*(j - 1));
        }
        *j = std::move(key);
    }
}

#endif
