#pragma once
#ifndef SORT_H_
#define SORT_H_

#include <vector>


template <typename Comparable>
void insertionSort(std::vector<Comparable>& array, int left, int right)
{
    for (int i = left + 1; i <= right; ++i)
    {
        Comparable key = array[i];
        int j = i;
        while (j > 0 && array[j - 1] > key)
        {
            array[j] = std::move(array[j - 1]);
            --j;
        }
        array[j] = std::move(key);
    }
}

template <typename Comparable>
void insertionSort(std::vector<Comparable>& array)
{
    insertionSort(array, 0, array.size() - 1);
}

template <typename Comparable>
void bubbleSort(std::vector<Comparable>& array)
{
    for (int i = 0; i < array.size(); ++i)
    {
        for (int j = 0; j < array.size() - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                using std::swap;
                swap(array[j], array[j + 1]);
            }
        }
    }
}

template <typename Comparable>
void selectiionSort(std::vector<Comparable>& array)
{
    for (int i = 0; i < array.size() - 1; ++i)
    {
        int minPos = i;
        Comparable min = array[i];
        for (int j = i + 1; j < array.size(); ++j)
        {
            if (array[j] < min)
            {
                minPos = j;
                min = array[j];
            }
        }
        using std::swap;
        swap(array[i], array[minPos]);
    }
}

//使用shell不理想增量排序
template <typename Comparable>
void shellSort(std::vector<Comparable>& array)
{
    for (int gap = array.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < array.size(); ++i)
        {
            //使用插入排序
#if 0       //数据结构与算法分析的插入排序
            Comparable tmp = std::move(array[i]);
            int j = i;
            for (; j >= gap && tmp < array[j - gap]; j -= gap)
            {
                array[j] = std::move(array[j - gap]);
            }
            a[j] = std::move(tmp);
#else       //算法导论的插入排序
            Comparable key = std::move(array[i]);
            int j = i;
            while (j >= gap && key < array[j - gap])
            {
                array[j] = std::move(array[j - gap]);
                j -= gap;
            }
            array[j] = std::move(key);
#endif
        }
    }
}

template <typename Comparable>
class HeapSort
{
public:
    void operator()(std::vector<Comparable>& array)
    {
        for (int i = array.size() / 2 - 1; i >= 0; --i)
        {
            percolateDown(array, i, array.size());
        }
        for (int j = array.size() - 1; j > 0; --j)
        {
            using std::swap;
            swap(array[0], array[j]);
            percolateDown(array, 0, j);
        }
    }
private:
    int leftChild(int hole)
    {
        return 2 * hole + 1;
    }
    void percolateDown(std::vector<Comparable>& array, int hole, int size)
    {
        int child = leftChild(hole);
        Comparable tmp = std::move(array[hole]);
        while (child < size)
        {
            if (child < size - 1 && array[child] < array[child + 1])
            {
                ++child;
            }
            if (tmp < array[child])
            {
                array[hole] = std::move(array[child]);
            }
            else
            {
                break;
            }
            hole = child;
            child = leftChild(hole);
        }
        array[hole] = std::move(tmp);
    }
};

template <typename Comparable>
class MergeSort
{
    using ArrayType = std::vector<Comparable>;
public:
    void operator()(ArrayType& array)
    {
        ArrayType tmpArray(array.size());
        mergeSort(array, tmpArray, 0, array.size() - 1);
    }
private:
    void mergeSort(ArrayType& array, ArrayType& tmpArray, int left, int right)
    {
        if (left < right)
        {
            int center = (left + right) / 2;
            mergeSort(array, tmpArray, left, center);
            mergeSort(array, tmpArray, center + 1, right);
            merge(array, tmpArray, left, center + 1, right);
        }
    }
    void merge(ArrayType& array, ArrayType& tmpArray, int leftBegin, int rightBegin, int rightEnd)
    {
        int leftEnd = rightBegin - 1;
        int tmpPos = leftBegin;
        int numElements = rightEnd - leftBegin + 1;

        while (leftBegin <= leftEnd && rightBegin <= rightEnd)
        {
            if (array[leftBegin] <= array[rightBegin])
            {
                tmpArray[tmpPos++] = std::move(array[leftBegin++]);
            }
            else
            {
                tmpArray[tmpPos++] = std::move(array[rightBegin++]);
            }
        }
        while (leftBegin <= leftEnd)
        {
            tmpArray[tmpPos++] = std::move(array[leftBegin++]);
        }
        while (rightBegin <= rightEnd)
        {
            tmpArray[tmpPos++] = std::move(array[rightBegin++]);
        }
        
        for (int i = 0; i < numElements; ++i, --rightEnd)
        {
            array[rightEnd] = std::move(tmpArray[rightEnd]);
        }
    }
};

template <typename Comparable>
void simpleQuickSort(std::vector<Comparable>& array)
{
    if (array.size() > 1)
    {
        std::vector<Comparable> smaller, same, larger;
        auto chosenItem = array[array.size() / 2];

        for (auto& item : array)
        {
            if (item < chosenItem)
            {
                smaller.push_back(std::move(item));
            }
            else if (item > chosenItem)
            {
                larger.push_back(std::move(item));
            }
            else
            {
                same.push_back(item);
            }
        }

        simpleQuickSort(smaller);
        simpleQuickSort(larger);

        std::move(std::begin(smaller), std::end(smaller), std::begin(array));
        std::move(std::begin(same), std::end(same), std::begin(array) + smaller.size());
        std::move(std::begin(larger), std::end(larger), std::begin(array) + smaller.size() + same.size());
    }
}

template <typename Comparable>
class QuickSort 
{
public:
    void operator()(std::vector<Comparable>& array)
    {
        quickSort(array, 0, array.size() - 1);
    }
private:
    const Comparable& median3(std::vector<Comparable>& array, int left, int right)
    {
        using std::swap;

        int center = (left + right) / 2;
        if (array[center] < array[left])
        {
            swap(array[center], array[left]);
        }
        if (array[right] < array[left])
        {
            swap(array[right], array[left]);
        }
        if (array[right] < array[center])
        {
            swap(array[right], array[center]);
        }

        swap(array[center], array[right - 1]);
        return array[right - 1];
    }
    void quickSort(std::vector<Comparable>& array, int left, int right)
    {
        using std::swap;

        if (left + 10 <= right)
        {
            const auto& pivot = median3(array, left, right);

            int i = left, j = right - 1;
            while (true)
            {
                while (array[++i] < pivot) {}
                while (array[--j] > pivot) {}

                if (i < j)
                {
                    swap(array[i], array[j]);
                }
                else
                {
                    break;
                }
            }
            swap(array[i], array[right - 1]);

            quickSort(array, left, i - 1);
            quickSort(array, i + 1, right);
        }
        else
        {
            insertionSort(array, left, right);
        }
    }
};
#endif