#include "expressiontree.h"
#include "infix2postfix.h"
#include <stack>
#include <utility>

static bool IsOperator(const std::string &str)
{
    bool operatorFlag = false;
    if ("+" == str || "-" == str || "*" == str || "/" == str)
    {
        operatorFlag = true;
    }

    return operatorFlag;
}

static zy::BinaryTree<std::string> ConstructExpressionTree(std::stack<std::string> &postfix)
{
    std::stack<zy::BinaryTree<std::string>> interTreeStack;
    while (!postfix.empty())
    {
        std::string str = postfix.top();
        postfix.pop();
        if (IsOperator(str))
        {
            auto preTop = interTreeStack.top();
            interTreeStack.pop();
            
            auto top = interTreeStack.top();
            interTreeStack.pop();

            zy::BinaryTree<std::string> operatorTree{ str };
            operatorTree.insertLeft(std::move(top));
            operatorTree.insertRight(std::move(preTop));
            interTreeStack.push(std::move(operatorTree));
        }
        else
        {
            zy::BinaryTree<std::string> operandTree{ str };
            interTreeStack.push(std::move(operandTree));
        }
    }
    return interTreeStack.top();
}

zy::BinaryTree<std::string> ExpressiionTree(const std::string & str)
{
    std::stack<std::string> postifx = Infix2Postfix(str);
    return ConstructExpressionTree(postifx);
}
