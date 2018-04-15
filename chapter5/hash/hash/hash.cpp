#include "hash.h"

int SimpleStrHash1(const std::string &str, int tableSize)
{
    unsigned int hashVal = 0;

    for (char ch : str)
    {
        hashVal += ch;
    }
    return hashVal % tableSize;
}

int SimpleStrHash2(const std::string &str, int tableSize)
{
    return (str[0] + str[1] * 27 + str[2] * 729) % tableSize;
}

int GoodStrHash(const std::string &str, int tableSize)
{
    unsigned int hashVal = 0;

    for (char ch : str)
    {
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % tableSize;
}
