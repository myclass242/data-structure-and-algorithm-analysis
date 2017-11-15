#include "infix2postfix.h"
#include <cctype>
#include <map>
#include <iostream>
#include <cstdbool>

std::map<std::string, int> operatorPriority = 
{
    {"+", 0},
    {"-", 0},
    {"*", 1},
    {"/", 1}
};

static void OperandHandler(const std::string &str, std::stack<std::string> &operand)
{
    if (!str.empty())
    {
        operand.push(str);
    }
}

static void OperatorHandler(const std::string &str, std::stack<std::string> &operatorChar, std::stack<std::string> &operand)
{
    if (str.empty())
    {
        return;
    }

    if ("+" == str || "-" == str ||
        "*" == str || "/" == str)
    {
        while (true)
        {
            if (operatorChar.empty() || "(" == operatorChar.top() || operatorPriority[str] > operatorPriority[operatorChar.top()])
            {
                operatorChar.push(str);
                break;
            }
            else
            {
                operand.push(operatorChar.top());
                operatorChar.pop();
            }
        }
    }
    else if ("(" == str)
    {
        operatorChar.push(str);
    }
    else if (")" == str)
    {
        while (operatorChar.top() != "(")
        {
            operand.push(operatorChar.top());
            operatorChar.pop();
        }
        operatorChar.pop();
    }
    else if (" " == str)
    {
        //do nothing
    }
    else
    {
        std::cout << "invalid operaotr : " << str << std::endl;
        exit(EXIT_FAILURE);
    }
}

std::stack<std::string> Infix2Postfix(const std::string & expression)
{
    std::stack<std::string> operatorChar;
    std::stack<std::string> operand;
    std::string str;
    bool isOperand = false;
    for (const auto &ch : expression)
    {
        if (std::isdigit(ch) || '.' == ch)
        {
            isOperand = true;
            str.push_back(ch);
        }
        else
        {
            if (isOperand)
            {
                OperandHandler(str, operand);
                str.clear();
                isOperand = false;
            }
            std::string operatorStr{ ch };
            OperatorHandler(operatorStr, operatorChar, operand);
        }
    }
    if (isOperand)
    {
        OperandHandler(str, operand);
    }
    while (!operatorChar.empty())
    {
        operand.push(operatorChar.top());
        operatorChar.pop();
    }
    
    //反转操作数栈
    std::stack<std::string> postFix;
    while (!operand.empty())
    {
        postFix.push(operand.top());
        operand.pop();
    }
    return postFix;
}

