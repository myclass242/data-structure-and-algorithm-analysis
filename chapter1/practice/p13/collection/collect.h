#pragma once
#ifndef COLLECT_H
#define COLLECT_H
#include<iostream>
#include<cstdbool>
#define SIZE 1000

template<typename Object>
class Collection
{
public:
    typedef Object type;
    Collection(int sz = 0)
        :size(sz)
    {}

    Collection(const Collection<Object> &cl)
        :size(cl.size)
    {
        for (int i = 0; i < size; ++i)
        {
            members[i] = cl.members[i];
        }
    }

    Collection &operator=(const Collection<Object> &cl)
    {
        size = cl.size;
        for (int i = 0; i < size; ++i)
        {
            members[i] = cl.members[i];
        }
        return *this;
    }

    bool IsEmpty(void) const
    {
        return size == 0 ? true : false;
    }

    void MakeEmpty(void)
    {
        size = 0;
    }

    int Insert(const Object &oj, int pos)
    {
        if (size == SIZE)
        {
            std::cout << "No space to insert" << std::endl;
            return SIZE + 1;
        }
        if (pos >= size)
        {
            members[size] = oj;
            ++size;
            return size - 1;
        }
        for (int i = size; i > pos; --i)
        {
            members[i] = members[i - 1];
        }
        members[pos] = oj;
        ++size;
        return pos;
    }

    void Remove(int pos)
    {
        if (pos >= size)
            return;
        while (pos < size)
        {
            members[pos] = members[pos + 1];
            ++pos;
        }
        --size;
    }

    Object FindMin(void) const
    {
        Object max = members[0];
        for (int n = 0; n < size; ++n)
        {
            max = max > members[n] ? max : members[n];
        }
        return max;
    }

    Object FindMax(void) const
    {
        Object min = members[0];
        for (int n = 0; n < size; ++n)
        {
            min = min < members[n] ? min : members[n];
        }
        return min;
    }
private:
    type members[SIZE];
    int size;
};
#endif // COLLECTION_H
