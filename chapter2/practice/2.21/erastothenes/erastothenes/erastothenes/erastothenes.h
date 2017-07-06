#pragma once
#ifndef ERASTOTHENES_H_
#define ERASTOTHENES_H_
#include <vector>
/*
* 厄拉多塞筛：厄拉多塞是一位古希腊数学家，他在寻找素数时，采用了一种与众不同的方法：
* 先将2－N的各数放入表中，然后在2的上面画一个圆圈，然后划去2的其他倍数；
* 第一个既未画圈又没有被划去的数是3，将它画圈，再划去3的其他倍数；
* 现在既未画圈又没有被划去的第一个数 是5，将它画圈，并划去5的其他倍数……依次类推，一直到所有小于或等于N的各数都画了圈或划去为止。
* 这时，表中画了圈的以及未划去的那些数正好就是小于 N的素数。
* 
*/
std::vector<int> SearchPrimeNumberByErastothenes(int n);
#endif