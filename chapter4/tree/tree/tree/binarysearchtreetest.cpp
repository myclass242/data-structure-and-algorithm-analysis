#include <random>
#include <iostream>
#include <gtest\gtest.h>
#include "binarysearchtree.h"

TEST(TreeTest, bstTest)
{
    zy::BinarySearchTree<int> t1;
    ASSERT_TRUE(t1.empty());

    std::default_random_engine e;
    std::uniform_int_distribution<int> r(1, 99);
    for (int k = 0; k < 20; ++k)
    {
        t1.insert(std::move(r(e)));
    }
    ASSERT_FALSE(t1.empty());
    t1.printTree(std::cout);
    std::cout << std::endl;
    ASSERT_TRUE(t1.contain(8));
    t1.remove(8);
    ASSERT_FALSE(t1.contain(8));
    t1.printTree(std::cout);
    std::cout << std::endl;
    ASSERT_EQ(15, t1.findMin());
    ASSERT_EQ(97, t1.findMax());
    auto t2 = t1;
    t2.printTree(std::cout);
    std::cout << std::endl;
    auto t3 = std::move(t2);
    std::cout << "after std::move(t2): ";
    t2.printTree(std::cout);
    std::cout << std::endl;
    t3.printTree(std::cout);
    std::cout << std::endl;
    t2 = t3;
    t2.printTree(std::cout);
    std::cout << std::endl;
    t2.makeEmpty();
    ASSERT_TRUE(t2.empty());
}
