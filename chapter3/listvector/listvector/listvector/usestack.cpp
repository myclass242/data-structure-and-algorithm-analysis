#include "usestack.h"
#include <cstdbool>
#include <iostream>

void BalanceSigned(std::ifstream &in)
{
	zy::stack<char> st;
	char ch;
	while (in.get(ch))
	{
		switch (ch)
		{
			case '(':
			case '[':
			case '{':
			{
				st.push(ch);
				break;
			}
			case ')':
			{
				if ((st.size() <= 0) || (st.top() != '('))
				{
					std::cout << "illegal character matching: ) with " << st.top() << std::endl;
					return;
				}
				st.pop();
				std::cout << "character matching: ()" << std::endl;
				break;
			}
			case ']':
			{
				if ((st.size() <= 0) || (st.top() != '['))
				{
					std::cout << "illegal character matching: ] with " << st.top() << std::endl;
					return;
				}
				st.pop();
				std::cout << "character matching: []" << std::endl;
				break;
			}
			case '}':
			{
				if ((st.size() <= 0) || (st.top() != '{'))
				{
					std::cout << "illegal character matching: } with " << st.top() << std::endl;
					return;
				}
				st.pop();
				std::cout << "character matching: {}" << std::endl;
				break;
			}
			default:
				break;
		}
	}
}
