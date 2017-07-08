#pragma once
#ifndef ZYALG_H_
#define ZYALG_H_
#include <iostream>

/* 对数据结构的操作算法 */

namespace zy{

//template <typename Container>
//auto begin(Container &lst) ->decltype(lst.begin())
//{
//	return lst.begin();
//}
//
//template <typename Container>
//auto begin(const Container &lst) ->decltype(lst.cbegin())
//{
//	return lst.cbegin();
//}

/* 每隔一项删除容器中的元素 */
template <typename Container>
void RemoveEveryOtherItem(Container &lst)
{
	auto begin = lst.begin();
	while (begin != lst.end())
	{
		begin = lst.erase();
		if (begin != lst.end())
		{
			++begin;
		}
	}
}

/* 打印容器中的元素 */
template <typename Container>
void Print(const Container &lst, std::ostream &out)
{
	if (lst.empty())
	{
		out << "empty" << std::endl;
		return;
	}
	auto cbegin = lst.cbegin();
	out << "[ " << *cbegin++;
	while (cbegin != lst.cend())
	{
		out << ", " << *cbegin++;
	}
	out << " ]" << std::endl;
}
}

#endif
