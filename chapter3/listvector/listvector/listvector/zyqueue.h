#pragma once
#ifndef ZYQUEUE_H_
#define ZYQUEUE_H_

#include <stdlib.h>
#include <initializer_list>
#include <exception>
#include <string.h>
#include "zylist.h"

//#define IMPLE_BY_ARRAY

namespace zy {
    //由循环数组实现队列
#ifdef IMPLE_BY_ARRAY
template<typename Object, size_t maxSize = 100>
class queue
{
public:
    typedef size_t SizeType;
    typedef typename Object ValueType;
public:
    queue()
        :theFront(1), theBack(0), theSize(0)
    {
        initArray();
    }

    explicit queue(queue &oth)
        :theFront(oth.theFront), theBack(oth.theBack), theSize(oth.theSize)
    {
        initArray();
        memcpy(theArray, oth.theArray, maxSize);
    }

    queue(const std::initializer_list<ValueType> &li)
        :queue()
    {
        for (const auto &elem : li)
        {
            push(elem);
        }
    }

    void push(const ValueType &item)
    {
        ValueType newItem = item;
        do_push(std::move(newItem));
    }

    void push(ValueType &&item)
    {
        do_push(std::move(item));
    }

    ValueType &back()
    {
        if (isEmpty())
        {
            exit(EXIT_FAILURE);
        }

        return theArray[theBack];
    }

    const ValueType &back() const
    {
        if (isEmpty())
        {
            exit(EXIT_FAILURE);
        }

        return theArray[theBack];
    }

    void pop()
    {
        if (isEmpty())
        {
            exit(EXIT_FAILURE);
        }

        ++theFront;
        --theSize;
    }

    ValueType &front()
    {
        if (isEmpty())
        {
            exit(EXIT_FAILURE);
        }

        return theArray[theFront];
    }

    const ValueType &front() const
    {
        if (isEmpty())
        {
            exit(EXIT_FAILURE);
        }

        return theArray[theFront];
    }

    SizeType size() const
    {
        return theSize;
    }

    SizeType capacity() const
    {
        return maxSize;
    }

    bool isEmpty(void) const
    {
        return 0 == theSize;
    }
private:
    bool isFull(void) const
    {
        return theSize == maxSize;
    }

    SizeType increaseIdx(SizeType &idx)
    {
        ++idx;
        idx = idx == maxSize ? 0 : idx;
        return idx;
    }

    void do_push(ValueType &&item)
    {
        if (!isFull())
        {
            theArray[increaseIdx(theBack)] = std::move(item);
            ++theSize;
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }

    void initArray(void)
    {
        theArray = new ValueType[maxSize];
    }
private:
    SizeType theFront = 1;
    SizeType theBack = 0;
    SizeType theSize = 0;
    ValueType *theArray;
};
#else
template<typename Object>
class queue : protected list<Object>
{
    typedef typename Object ValueType;
    typedef size_t SizeType;
public:
    //使用list的构造函数
    using list::list;

    ~queue() = default;

    void push(ValueType item)
    {
        list::push_back(std::move(item));
    }

    void pop(void)
    {
        return list::pop_front();
    }

    ValueType &back(void)
    {
        return list::back();
    }

    const ValueType &back(void) const
    {
        return list::back();
    }

    ValueType &front(void)
    {
        return list::front();
    }

    const ValueType &front(void) const
    {
        return list::front();
    }

    bool isEmpty(void) const
    {
        return list::empty();
    }

    SizeType size(void) const
    {
        return list::size();
    }
};
#endif
}

#endif
