#include "postfixnotation.h"
#include <map>
#include <functional>
#include <stdlib.h>
#include <cassert>

std::map<int, int> OpCharPriority =
{
	{'+', 0},
	{'-', 0},
	{'*', 1},
	{'/', 1}
};

static int Add(int left, int right)
{
	return left + right;
}

static int Minus(int left, int right)
{
	return left - right;
}

static int Multiply(int left, int right)
{
	return left * right;
}

static int Divide(int left, int right)
{
	assert(0 != right);
	return left / right;
}

std::map<int, std::function<int(int, int)>> mapCalc
{
	{ '+', Add },
	{ '-', Minus },
	{ '*', Multiply },
	{ '/', Divide }
};

static int CalculationPostfixNotation(zy::stack<int> &postfixNotation)
{
	int top = 0;
	int nextTop = 1;
    zy::stack<int> opCh;
	while (!postfixNotation.empty())
	{
		int tempChar = postfixNotation.top();
		postfixNotation.pop();
		switch (tempChar)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		{
            top = opCh.top();
            opCh.pop();
            nextTop = opCh.top();
            opCh.pop();
			top = mapCalc[tempChar](nextTop, top);
            opCh.push(top);
			break;
		}
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		{
            opCh.push(tempChar);
			break;
		}
		default:
			break;
		}
	}
	return top;
}

int PostfixNotation(const std::string &infixNotation)
{
	zy::stack<int> operationalCharacter;
	zy::stack<int> operand;
	for (const auto &charact : infixNotation)
	{
		switch (charact)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		{
			while (true)
			{
				if (operationalCharacter.empty() || operationalCharacter.top() == '(')
				{
					operationalCharacter.push(charact);
					break;
				}
				else if (OpCharPriority[charact] > OpCharPriority[operationalCharacter.top()])
				{
					operationalCharacter.push(charact);
					break;
				}
				else
				{
					operand.push(operationalCharacter.top());
					operationalCharacter.pop();
				}
			};
            break;
		}
		case '(':
		{
			operationalCharacter.push(charact);
			break;
		}
		case ')':
		{
			while (operationalCharacter.top() != '(')
			{
				operand.push(operationalCharacter.top());
				operationalCharacter.pop();
			}
			operationalCharacter.pop();
			break;
		}
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			operand.push(charact - '0');
			break;
		}
		default:
		{
			break;
		}
		}	
	}
	while (!operationalCharacter.empty())
	{
		operand.push(operationalCharacter.top());
		operationalCharacter.pop();
	}
	//ÄæÐò
	while (!operand.empty())
	{
		operationalCharacter.push(operand.top());
		operand.pop();
	}
	return CalculationPostfixNotation(operationalCharacter);
}
