#pragma once
#ifndef QUADRATIC_PROBE_HASH_TABLE_H_
#define QUADRATIC_PROBE_HASH_TABLE_H_

#include <vector>
#include <utility>
#include <iostream>
#include "primer.h"
#include "hash.h"

template<typename HashObject>
class QuadraticProbeHashTable
{
public:
    typedef typename HashObject ValueType;
    typedef std::size_t SizeType;
private:
    enum EntryType { ACTIVE, EMPTY, DELETED };
    struct HashEntry
    {
        HashEntry(const ValueType &e = ValueType{}, EntryType t = EMPTY)
            :item(e), info(t)
        {}
        HashEntry(ValueType &&e, EntryType t = EMPTY)
            :item(std::move(e)), info(t)
        {}
        ValueType item;
        EntryType info;
    };
public:
    explicit QuadraticProbeHashTable(SizeType size = 101)
        :hashTable(NextPrimer(size)), curSzie(0)
    {}
    QuadraticProbeHashTable(const QuadraticProbeHashTable &oth)
        :hashTable(oth.hashTable), curSzie(oth.curSzie)
    {}
    QuadraticProbeHashTable(QuadraticProbeHashTable &&oth)
        :hashTable(std::move(oth.hashTable)), curSzie(oth.curSzie)
    {
        oth.curSzie = 0;
    }
    ~QuadraticProbeHashTable()
    {}
    QuadraticProbeHashTable &operator=(const QuadraticProbeHashTable &oth)
    {
        hashTable = oth.hashTable;
        curSzie = oth.curSzie;
        return *this;
    }
    QuadraticProbeHashTable &operator=(QuadraticProbeHashTable &&oth)
    {
        hashTable = std::move(oth.hashTable);
        curSzie = oth.curSzie;
        oth.curSzie = 0;
        return *this;
    }
    bool insert(ValueType &&item)
    {
        SizeType pos = findPos(item);

        if (hashTable[pos].info == ACTIVE)
        {
            return false;
        }

        if (hashTable[pos].info == DELETED)
        {
            hashTable[pos].info = ACTIVE;
        }
        else
        {
            hashTable[pos].item = std::move(item);
            hashTable[pos].info = ACTIVE;
        }

        if (++curSzie * 10 > hashTable.size() * ratio4Rehash)
        {
            reHash();
        }
        return true;
    }
    bool insert(const ValueType &item)
    {
        ValueType temp = item;
        return insert(std::move(temp));
    }
    bool remove(const ValueType &item)
    {
        SizeType pos = findPos(item);
        
        if (hashTable[pos].info == ACTIVE)
        {
            hashTable[pos].info = DELETED;
            --curSzie;
            return true;
        }
        return false;
    }
    bool contain(const ValueType &item) const
    {
        SizeType pos = findPos(item);
        return hashTable[pos].info == ACTIVE;
    }
    friend std::ostream &operator<<(std::ostream &out, const QuadraticProbeHashTable<ValueType> &hashTable)
    {
        for (const auto &item : hashTable.hashTable)
        {
            if (out && item.info == ACTIVE)
            {
                out << item.item << ' ';
            }

            if (!out)
            {
                return out;
            }
        }
        return out;
    }
    void makeEmpty(void)
    {
        hashTable.clear();
        curSzie = 0;
    }
    SizeType size(void) const
    {
        return curSzie;
    }
private:
    SizeType findPos(const ValueType &item) const
    {
        SizeType probTimes = 0;
        SizeType pos = MyHash(item);
        while (hashTable[pos].info != EMPTY && hashTable[pos].item != item)
        {
            pos += prob(++probTimes);
            if (pos >= hashTable.size())
            {
                pos -= hashTable.size();
            }
        }
        return pos;
    }
    SizeType MyHash(const ValueType &item) const
    {
        static Hash<ValueType> hf;
        return hf(item) % hashTable.size();
    }
    SizeType prob(SizeType probTimes) const
    {
        return probTimes * probTimes;
    }
    void reHash(void)
    {
        auto hashTableSize = hashTable.size();
        auto oldHashTable = std::move(hashTable);
        hashTable.resize(NextPrimer(hashTableSize * 2));
        for (const auto &item : oldHashTable)
        {
            if (ACTIVE == item.info)
            {
                insert(item.item);
            }
        }
    }
private:
    std::vector<HashEntry> hashTable;
    SizeType curSzie;
    static const int ratio4Rehash = 4;
};

#endif
