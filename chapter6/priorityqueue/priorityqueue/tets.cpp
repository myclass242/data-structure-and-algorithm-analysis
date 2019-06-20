#include "BinaryHeap2.h"

#include <iostream>
#include <random>

const int LEN = 10;

int main(void)
{
    std::default_random_engine e;
    std::uniform_int_distribution<int> r(1, 9999);

    BinaryHeap2<int> bh(LEN);
    for (int k = 0; k < LEN; ++k)
    {
        bh.insert(r(e));
    }

    bh.remove(3);
    bh.increaseKey(3, 5000);
    bh.decreaseKey(7, 5000);
    int value = -1;
    while (!bh.isEmpty())
    {
        #if 0
        value = bh.findMin();
        bh.deleteMin();
        #else
        bh.deleteMin(value);
        #endif
        std::cout << value << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}
