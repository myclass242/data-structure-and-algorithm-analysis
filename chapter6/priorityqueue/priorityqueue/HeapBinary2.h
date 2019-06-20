#ifndef BINARY_HEAP2_H_
#define BINARY_HEAP2_H_

#include <vector>
#include <stdexcept>

// need the Compare can value-initiliazied
template <typename Compare>
class BinaryHeap2
{
    using SizeType = std::size_t;
public:
    explicit BinaryHeap2(int capacity = 100)
        : currentSize_(0)
    {
        if (capacity < 3)
        {
            capacity = 3;
        }
        array_.resize(capacity);
    }
    explicit BinaryHeap2(const std::vector<Compare>& items)
        : array_(items.size() + 10), currentSize_(items.size())
    {
        for (int k = 0; k < items.size(); ++k)
        {
            array_[k + 1] = items[k];
        }
        buildHeap();
    }
    bool isEmpty() const
    {
        return currentSize_ == 0;
    }
    const Compare& findMin() const
    {
        return array_.at(1);
    }
    void insert(const Compare& x)
    {
       Compare tmp = x;
       insert(std::move(tmp));
    }
    void insert(Compare&& x)
    {
        if (currentSize_ == array_.size() - 1)
        {
            array_.resize(2 * array_.size());
        }

        array_[0] = std::move(x);
        SizeType hole = ++currentSize_;
        for (; array_[0] < array_[hole / 2]; hole /= 2)
        {
            array_[hole] = std::move(array_[hole / 2]);
        }
        array_[hole] = std::move(array_[0]);
    }
    void deleteMin()
    {
        if (isEmpty())
        {
            throw std::range_error{"deleteMin"};
        }
        array_[1] = std::move(array_[currentSize_--]);
        percolateDown(1);
    }
    void deleteMin(Compare& min)
    {
        if (isEmpty())
        {
            throw std::range_error{"deleteMin"};
        }
        min = array_[1];
        array_[1] = std::move(array_[currentSize_--]);
        percolateDown(1);
    }
    void decreaseKey(int pos, Compare delta)
    {
        checkPosition(pos);

        array_[pos] -= delta;
        percolateUp(pos);
    }
    void increaseKey(int pos, Compare delta)
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
        Compare tmp = std::move(array_[hole]);
        SizeType child = 0;
        while (2 * hole <= currentSize_)
        {
            child = 2 * hole;
            if (child != currentSize_ && array_[child] > array_[child + 1])
            {
                ++child;
            }
            if (tmp > array_[child])
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

        Compare tmp = std::move(array_[hole]);
        SizeType child = 0;
        for (; 2 * hole < currentSize_; hole = child)
        {
            child = 2 * hole;
            if (array_[child] > array_[child + 1])
            {
                ++child;
            }
            if (tmp > array_[child])
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
        Compare tmp = std::move(array_[hole]);
        SizeType parent = 0;
        for (; hole >= 1; hole = parent)
        {
            parent = hole / 2;
            if (parent > 0 && array_[parent] > tmp)
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
            throw std::range_error{"checkPosition"};
        }
    }

    std::vector<Compare> array_;
    SizeType currentSize_;
};

#endif
