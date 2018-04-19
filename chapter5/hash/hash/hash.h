#pragma once
#ifndef HASH_H_
#define HASH_H_

#include <string>
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
    size_t operator()(const std::string &str) const
    {
        size_t hashVal = 0;

        for (char ch : str)
        {
            hashVal = ch + 37 * hashVal;
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
