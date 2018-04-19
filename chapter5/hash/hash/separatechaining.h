#pragma once
#ifndef SEPARATE_CHAINING_H_
#define SEPARATE_CHAINING_H_

#include <iostream>
#include <forward_list>
#include <vector>
#include <utility>
#include <algorithm>
#include "primer.h"
#include "hash.h"

template <typename HashObj>
class SeparateChainingHash
{
public:
    typedef typename HashObj ValueType;
public:
    explicit SeparateChainingHash(size_t num = 101)
        :hashTable(NextPrimer(num)), curSize(0)
    {}
    SeparateChainingHash(const SeparateChainingHash &oth)
        :hashTable(oth.hashTable), curSize(oth.curSize)
    {}
    SeparateChainingHash(SeparateChainingHash &&oth)
        :hashTable(std::move(oth.hashTable)), curSize(oth.curSize)
    {
        oth.curSize = 0;
    }
    ~SeparateChainingHash()
    {}
public:
    SeparateChainingHash & operator=(const SeparateChainingHash &oth)
    {
        hashTable = oth.hashTable;
        curSize = oth.curSize;
        return *this;
    }
    SeparateChainingHash *operator=(SeparateChainingHash &&oth)
    {
        hashTable = std::move(oth);
        curSize = oth.curSize;
        oth.curSize = 0;
        return *this;
    }
    void makeEmpty(void)
    {
        hashTable.clear();
        curSize = 0;
    }
    bool contain(const ValueType &item) const
    {
        const auto &whichList = hashTable[myHash(item)];
        return std::find(whichList.cbegin(), whichList.cend(), item) != whichList.cend();
    }
    bool remove(const ValueType &item)
    {
        auto &whichList = hashTable[myHash(item)];
        typename std::forward_list<ValueType>::iterator posBefore = whichList.before_begin();
        for (; std::next(posBefore) != whichList.end(); ++posBefore)
        {
            if (item == *std::next(posBefore))
            {
                whichList.erase_after(posBefore);
                --curSize;
                return true;
            }
        }
        return false;
    }
    bool insert(ValueType &&item)
    {
        auto &whichList = hashTable[myHash(item)];

        if (std::find(whichList.cbegin(), whichList.cend(), item) != whichList.cend())
        {
            return false;
        }

        whichList.push_front(std::move(item));
        if (++curSize > hashTable.size())
        {
            reHash();
        }
        
        return true;
    }
    bool insert(const ValueType &item)
    {
        ValueType tmp = item;
        return insert(std::move(tmp));
    }
    void show(void) const
    {
        size_t arrayIdx = 0;
        for (const auto &list : hashTable)
        {
            if (!list.empty())
            {
                std::cout << "Hash Table cell " << arrayIdx << ':' << ' ';
                for (const auto &item : list)
                {
                    std::cout << item << ';';
                }
                std::cout << std::endl;
            }
            ++arrayIdx;
        }
    }
private:
    size_t myHash(const ValueType &item) const
    {
        static Hash<ValueType> hf;
        return hf(item) % hashTable.size();
    }
    void reHash(void)
    {
        auto oldTable = std::move(hashTable);
        hashTable.resize(NextPrimer(2 * oldTable.size()));

        for (const auto &list : oldTable)
        {
            for (const auto &item : list)
            {
                hashTable[myHash(item)].push_front(item);
            }
        }
    }
private:
    std::vector<std::forward_list<ValueType>> hashTable;
    size_t curSize;
};

#endif
