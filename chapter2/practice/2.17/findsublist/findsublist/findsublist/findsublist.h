#pragma once
#ifndef FINDSUBLIST_H_
#define FINDSUBLIST_H_
#include <vector>
/*
* a.�ҳ����е���С�����к�
* b.�ҳ����е���С����������֮��
* c.�ҳ����е���������г˻�
*/

int FindMinSubList(const std::vector<int> &vi);

/* Ѱ�������и����������еĺ���С���Ǹ������� 
* ��������������У��򷵻� INT_MAX
*/
int FindMinSubListInPlusSubList(const std::vector<int> &vi);

int FindMaxSubListOfProduct(const std::vector<int> &vi);
#endif