#pragma once
#ifndef INFIX2POSTFIX_H_
#define INFIX2POSTFIX_H_

#include <string>
#include <stack>

std::stack<std::string> Infix2Postfix(const std::string &expression);

#endif

