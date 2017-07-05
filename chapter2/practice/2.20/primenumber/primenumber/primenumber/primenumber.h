#pragma once
#ifndef PRIMENUMBER_H_
#define PRIMERNUMBER_H_
#include <cstdbool>

/*
* 编写程序确认正整数N是否是素数
* 数学方法：对正整数N，如果2到根号N之间的所有整数去除，准无法整除，则N为素数，
*/
bool IsPrimeNumber(int n);

#endif