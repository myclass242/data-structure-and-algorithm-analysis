#pragma once
#ifndef FUNCSOLUTION_H_
#define FUNCSOLUTION_H_
#include <functional>
/*
* ��������������Ĳ��Ҵ���������ʹ��f(low)��f(high)�����෴����ô��low��high֮���Ȼ����һ����
* ��������
*/

double SeekContinuousFunctionSolution(const std::function<double(double)> &, double, double);
#endif