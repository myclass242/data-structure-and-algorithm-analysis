#include "test.h"
#include <random>
#include <functional>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

static void printVector(const std::vector<int>& array, std::string usage)
{
    std::cout << std::setw(15) <<usage << ":";
    for (int i = 0; i < array.size(); ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void testSort(void)
{
    std::default_random_engine e;
    std::random_device rd;
    std::uniform_int_distribution<int> g(100, 1000);
    auto r = std::bind(g, e);

    std::vector<int> maternal;
    for (int i = 0; i < 55; ++i)
    {
        //maternal.push_back(r());
        maternal.push_back(g(rd));
    }
    printVector(maternal, "maternal");

    auto bubbleSortVector = maternal;
    bubbleSort(bubbleSortVector);
    printVector(bubbleSortVector, "bubbleSort");

    auto heapSortVector = maternal;
    HeapSort<int> heapSort;
    heapSort(heapSortVector);
    printVector(heapSortVector, "heapSort");

    auto insertionSortVector = maternal;
    insertionSort(insertionSortVector);
    printVector(insertionSortVector, "insertionSort");

    auto selectionSortVector = maternal;
    selectiionSort(selectionSortVector);
    printVector(selectionSortVector, "selectionSort");

    auto shellSortVector = maternal;
    shellSort(shellSortVector);
    printVector(shellSortVector, "shellSort");

    auto mergeSortVector = maternal;
    MergeSort<int> mergeSort;
    mergeSort(mergeSortVector);
    printVector(mergeSortVector, "mergeSort");

    auto simpleQuickSortVector = maternal;
    simpleQuickSort(simpleQuickSortVector);
    printVector(simpleQuickSortVector, "simpleQuickSort");

    auto quickSortVector = maternal;
    QuickSort<int> quickSort;
    quickSort(quickSortVector);
    printVector(quickSortVector, "quickSort");

    auto bucketSortVector = maternal;
    radixSort(bucketSortVector);
    printVector(bucketSortVector, "bucketSort");
}

void createRandomNumberFile(const std::string & fileName)
{
    std::random_device rd;
    std::uniform_int_distribution<int> g;

    std::ofstream out(fileName, std::ios::out | std::ios::trunc);

    for (uint64_t i = 0; i < UINT16_MAX; ++i)
    //for (int i = 0; i < INT16_MAX; ++i)
    {
        out << g(rd) << " ";
    }
    out.close();
}

void sortRandomNumberFile(const std::string & fileName)
{
    std::ifstream in(fileName);
    std::vector<int> array(UINT16_MAX);
    while (in)
    {
        int num;
        in >> num;
        array.push_back(num);
    }
    QuickSort<int> quickSort;
    quickSort(array);
    printVector(array, "sortRandomNumberFile");
}
