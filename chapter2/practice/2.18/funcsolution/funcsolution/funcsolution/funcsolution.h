#pragma once
#ifndef FUNCSOLUTION_H_
#define FUNCSOLUTION_H_
#include <functional>
/*
* 如果函数是连续的并且存在两个点使的f(low)和f(high)符号相反，那么在low和high之间必然存在一个根
* 求出这个跟
*/

double SeekContinuousFunctionSolution(const std::function<double(double)> &, double, double);
#endif