#pragma once
#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include <vector>
#include <exception>

template <typename Comparable>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity = 100)
        : currentSize(0)
    {
        array.reserve(capacity);
    }
    explicit BinaryHeap(const std::vector<Comparable>& items)
        : array(items.size() + 10), currentSize(items.size())
    {
        for (int i = 0; i < items.size(); ++i)
        {
            array[i + 1] = items[i];
        }
        buildHeap();
    }

    bool isEmpty() const
    {
        return currentSize > 0;
    }
    const Comparable& findMin() const;

    void insert(const Comparable& x)
    {
        Comparable tmp = x;
        insert(std::move(tmp));
    }
    void insert(Comparable&& x)
    {
        if (currentSize == array.size() - 1)
        {
            array.resize(2 * array.size());
        }

        //percolate up
        array[0] = std::move(x);
        int hole = ++currentSize;

        for (; array[0] < array[hole / 2]; hole /= 2)
        {
            array[hole] = std::move(array[hole / 2]);
        }
        array[hole] = std::move(array[0]);
    }
    void deleteMin()
    {
        if (isEmpty())
        {
            throw UnderflowException{};
        }
        array[1] = std::move(array[currentSize--]);
        percolateDowm(1);
    }
    void deleteMin(Comparable& minItem)
    {
        if (isEmpty()) 
        {
            throw UnderflowException{};
        }

        minItem = std::move(array[1]);
        array[1] = std::move(array[currentSize--]);
        percolateDowm(1);
    }
    void decreaseKey(int pos, Comparable delta)
    {
        if (pos > currentSize)
        {
            throw std::exception{};
        }
        array[pos] -= delta;
        percolateUp(pos);
    }
    void increaseKey(int pos, Comparable delta)
    {
        if (pos > currentSize)
        {
            throw std::exception{};
        }
        array[pos] += delta;
        percolateDowm(pos);
    }
    void remove(int pos)
    {
        decreaseKey(pos, )
    }
    void makeEmpty()
    {
        currentSize = 0;
    }
private:
    void buildHeap()
    {
        for (int i = currentSize / 2; i > 0; --i)
        {
            percolateDowm(i);
        }
    }
    void percolateDowm(int hole)
    {
        Comparable tmp = std::move(array[hole]);
        int child = 0;

        for (; 2 * hole <= currentSize; hole = child)
        {
            child = 2 * hole;
            if (child != currentSize && array[child + 1] < array[child]) 
            {
                ++child;
            }
            if (array[child] < tmp)
            {
                array[hole] = std::move(array[child]);
            }
            else
            {
                break;
            }
        }
        array[hole] = std::move(tmp);
    }
    void percolateDown(int hole, bool twoChild)
    {
        if (!twoChild)
        {
            return percolateDowm(hole);
        }

        Comparable tmp = std::move(array[hole]);
        int child = 0;
        for (; hole * 2 < currentSize; hole = child)
        {
            child = 2 * hole;
            if (array[hole * 2 + 1] < array[hole * 2])
            {
                ++child;
            }
            if (array[child] < tmp)
            {
                array[hole] = std::move(array[child]);
            }
            else
            {
                break;
            }
        }
        array[hole] = std::move(tmp);
    }
    void percolateUp(int hole)
    {
        Comparable tmp = std::move(array[hole]);
        for (; hole / 2 >= 1; hole /= 2)
        {
            if (array[hole / 2] > tmp)
            {
                array[hole] = std::move(array[hole / 2]);
            }
            else
            {
                break;
            }
        }
        array[hole] = std::move(tmp);
    }

    int currentSize;
    std::vector<Comparable> array;
    Comparable MAX;
};

#endif