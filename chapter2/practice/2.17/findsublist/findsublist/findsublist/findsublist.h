#pragma once
#ifndef FINDSUBLIST_H_
#define FINDSUBLIST_H_
#include <vector>
/*
* a.找出序列的最小子序列和
* b.找出序列的最小的正子序列之和
* c.找出序列的最大子序列乘积
*/

int FindMinSubList(const std::vector<int> &vi);

/* 寻找序列中各个正子序列的和最小的那个子序列 
* 如果不存在正序列，则返回 INT_MAX
*/
int FindMinSubListInPlusSubList(const std::vector<int> &vi);

int FindMaxSubListOfProduct(const std::vector<int> &vi);
#endif