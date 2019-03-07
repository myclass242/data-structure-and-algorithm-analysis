#pragma once
#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <math.h>
#include "employee.h"

int SimpleStrHash1(const std::string &str, int tableSize);

int SimpleStrHash2(const std::string &str, int tableSize);

int GoodStrHash(const std::string &str, int tableSize);

template <typename HashObj>
struct Hash
{
    size_t operator()(const HashObj &itm) const;
};

template <>
struct Hash<std::string>
{
    static const std::size_t FACTOR = 37;
    size_t operator()(const std::string &str) const
    {
        size_t hashVal = 0;

        for (char ch : str)
        {
            hashVal = ch + FACTOR * hashVal;
        }
        return hashVal;
    }

    std::size_t operator()(const std::string& str, int start, int length, std::size_t preHashVal) const
    {
        std::size_t hashVal = preHashVal;
        std::size_t preVal = str[start - 1];
        for (int k = 0; k < length - 1; ++k)
        {
            preVal = FACTOR * preVal;
        }
        hashVal -= preVal;
        hashVal = str[start + length - 1] + FACTOR * hashVal;
        return hashVal;
    }

    std::size_t operator()(const std::string& str, int start, int length) const
    {
        std::size_t hashVal = 0;
        for (int i = 0; i < length; ++i)
        {
            hashVal = str[start + i] + FACTOR * hashVal;
        }
        return hashVal;
    }
};

template <>
struct Hash<int>
{
    size_t operator()(int x) const
    {
        return x;
    }
};

template <>
struct Hash<Employee>
{
    size_t operator()(const Employee &eple) const
    {
        static Hash<std::string> hs;
        return hs(eple.getName());
    }
};

#endif
