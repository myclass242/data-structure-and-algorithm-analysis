#include "BinaryHeap2.h"

#include <iostream>
#include <random>

const int LEN = 10;

int main(void)
{
    std::default_random_engine e;
    std::uniform_int_distribution<int> r(1, 9999);

    BinaryHeap2<int> bh(LEN);
    std::vector<int> vi;
    for (int k = 0; k < LEN; ++k)
    {
        bh.insert(r(e));
        vi.push_back(r(e));
    }

    bh.remove(3);
    bh.increaseKey(3, 5000);
    bh.decreaseKey(7, 5000);
    int value = -1;

    std::cout << "bh1" << '\n';
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
    std::cout << '\n';

    std::cout << "bh2" << '\n';
    BinaryHeap2<int> bh2(vi);
    while (!bh2.isEmpty())
    {
        #if 1
        value = bh2.findMin();
        bh2.deleteMin();
        #else
        bh2.deleteMin(value);
        #endif
        std::cout << value << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}
