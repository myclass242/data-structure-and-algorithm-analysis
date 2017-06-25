#pragma once
#ifndef FINDMAXLIST_H_
#define FINDMAXLIST_H_
#include <vector>
#include <tuple>
/*
* 求序列的最大子序列
*/
std::tuple<int, int, int> FindMaxList(const std::vector<int> &);

std::tuple<int, int, int> FindMaxList2(const std::vector<int> &);
#endif