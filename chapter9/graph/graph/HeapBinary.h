#pragma once
#ifndef HEAP_BINARY_H_
#define HEAP_BINARY_H_

#include <vector>
#include <stdexcept>
#include <functional>

// need the T can value-initiliazied
template <typename T, typename Com = std::less<T>, typename Equal = std::equal_to<T>>
class BinaryHeap
{
    using SizeType = std::size_t;
public:
    explicit BinaryHeap(int capacity = 7)
        : currentSize_(0)
    {
        array_.reserve(capacity);
        array_.push_back(T{});
    }
    explicit BinaryHeap(const std::vector<T>& items)
        : currentSize_(items.size())
    {
        array_.reserve(items.size() + 1);
        array_.push_back(T{});

        for (const auto& item : items)
        {
            array_.push_back(item);
        }
        buildHeap();
    }
    bool isEmpty() const
    {
        return currentSize_ == 0;
    }
    const T& findMin() const
    {
        return array_.at(1);
    }
    void insert(const T& x)
    {
        T tmp = x;
        insert(std::move(tmp));
    }
    void insert(T&& x)
    {
        if (currentSize_ == array_.size() - 1)
        {
            array_.resize(2 * array_.size());
        }

        array_[0] = std::move(x);
        SizeType hole = ++currentSize_;
        for (; comFunc_(array_[0], array_[hole / 2]); hole /= 2)
        {
            array_[hole] = std::move(array_[hole / 2]);
        }
        array_[hole] = std::move(array_[0]);
    }
    void deleteMin()
    {
        if (isEmpty())
        {
            throw std::range_error{ "deleteMin" };
        }
        array_[1] = std::move(array_[currentSize_--]);
        percolateDown(1);
    }
    void deleteMin(T& min)
    {
        if (isEmpty())
        {
            throw std::range_error{ "deleteMin" };
        }
        min = array_[1];
        array_[1] = std::move(array_[currentSize_--]);
        percolateDown(1);
    }
    int find(const T& value)
    {
        for (int i = 0; i < array_.size(); ++i)
        {
            if (equalFunc_(value, array_[i]))
            {
                return i;
            }
        }
        return -1;
    }
    void decreaseKey(int pos, T delta)
    {
        checkPosition(pos);

        array_[pos] -= delta;
        percolateUp(pos);
    }
    void decreaseKey(int pos)
    {
        checkPosition(pos);

        percolateUp(pos);
    }
    void increaseKey(int pos, T delta)
    {
        checkPosition(pos);

        array_[pos] += delta;
        percolateDown(pos);
    }
    void makeEmpty()
    {
        currentSize_ = 0;
    }
    void remove(int pos)
    {
        checkPosition(pos);

        if (pos == currentSize_)
        {
            --currentSize_;
        }
        array_[pos] = std::move(array_[currentSize_--]);
        percolateDown(pos);
    }
private:
    void percolateDown(int hole)
    {
        T tmp = std::move(array_[hole]);
        SizeType child = 0;
        while (2 * hole <= currentSize_)
        {
            child = 2 * hole;
            if (child != currentSize_ && comFunc_(array_[child + 1], array_[child]))
            {
                ++child;
            }
            if (comFunc_(array_[child], tmp))
            {
                array_[hole] = std::move(array_[child]);
            }
            else
            {
                break;
            }
            hole = child;
        }
        array_[hole] = std::move(tmp);
    }
    void buildHeap()
    {
        for (int k = currentSize_ / 2; k > 0; --k)
        {
            percolateDown(k);
        }
    }
    void percolateDown(int hole, bool twoChild)
    {
        if (!twoChild)
        {
            percolateDown(hole);
        }

        T tmp = std::move(array_[hole]);
        SizeType child = 0;
        for (; 2 * hole < currentSize_; hole = child)
        {
            child = 2 * hole;
            if (comFunc_(array_[child + 1], array_[child]))
            {
                ++child;
            }
            if (comFunc_(array_[child], tmp))
            {
                array_[hole] = std::move(array_[child]);
            }
            else
            {
                break;
            }
        }
        array_[hole] = std::move(tmp);
    }
    void percolateUp(int hole)
    {
        T tmp = std::move(array_[hole]);
        SizeType parent = 0;
        for (; hole >= 1; hole = parent)
        {
            parent = hole / 2;
            if (parent > 0 && comFunc_(tmp, array_[parent]))
            {
                array_[hole] = std::move(array_[parent]);
            }
            else
            {
                break;
            }
        }
        array_[hole] = std::move(tmp);
    }
    void checkPosition(int pos)
    {
        if (pos < 1 || pos > currentSize_)
        {
            throw std::range_error{ "checkPosition" };
        }
    }

    std::vector<T> array_;
    SizeType currentSize_;
    Com comFunc_;
    Equal equalFunc_;
};

#endif