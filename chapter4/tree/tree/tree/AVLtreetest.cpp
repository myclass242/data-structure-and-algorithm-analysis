#include <gtest\gtest.h>
#include "AVLtree.h"
#include <iostream>
#include <random>
#include <stdint.h>
#include <fstream>

TEST(AVLtreeTest, avlTest)
{
    zy::AVLtree<int> avlTree1;
    std::default_random_engine e;
    std::uniform_int_distribution<int> r;
    for (uint64_t k = 0; k < UINT64_MAX; ++k)
    {
        avlTree1.insert(r(e));
    }
    std::ofstream out;
    out.open("nums.txt");
    avlTree1.inorderPrint(out);
}
