#include "test.h"
#include <iostream>

void TestTree(void)
{
    zy::Tree<int> treeInt1;
    for (int k = 0; k != 100; ++k)
    {
        treeInt1.insert(k);
    }
    zy::Tree<int> treeInt2 = treeInt1;
    
    std::cout << "treeInt1.PreorderTraversal(std::cout)" << std::endl;
    treeInt1.PreorderTraversal(std::cout);
    std::cout << "treeInt2.PreorderTraversal(std::cout)" << std::endl;
    treeInt2.PreorderTraversal(std::cout);
    std::cout << "treeInt1.PostorderTraversal(std::cout)" << std::endl;
    treeInt1.PostorderTraversal(std::cout);
    std::cout << "treeInt2.PostorderTraversal(std::cout)" << std::endl;
    treeInt2.PostorderTraversal(std::cout);
}

void TestInfix2Postfix(void)
{
    std::stack<std::string> postFix = Infix2Postfix("(3.1415926+423)*(5.0+6)*7.7");
    while (!postFix.empty())
    {
        std::cout << postFix.top() << ' ';
        postFix.pop();
    }
}

void TestExpressionTree(void)
{
    zy::BinaryTree<std::string> expressionTree = ExpressiionTree("3+(4-5)*6+7");
    expressionTree.preorderPrint(std::cout);
    expressionTree.inorderPrint(std::cout);
    expressionTree.postorderPrint(std::cout);
}



