#include "test.h"
#include <iostream>
#include <string.h>
#include <gtest\gtest.h>

int main(int argc, char *argv[])
{
    //TestTree();

    //TestInfix2Postfix();

    TestExpressionTree();
    
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    system("pause");
    return 0;
}

