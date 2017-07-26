#pragma once
#ifndef ZYSTACK_H_
#define ZYSTACK_H_
#include "zyforwardlist.h"
#include "zyvector.h"

namespace zy {
	/* 使用单链表实现stack */
template <typename Object>
class stack:protected ForwardList<Object>
{
public:
	typedef typename Object ValueType;
	using ForwardList::ForwardList;

	stack() = default;

	stack(const stack &oth)
		:ForwardList(oth)
	{}

	stack(stack &&oth)
		:ForwardList(std::move(oth))
	{}

	void push(const ValueType &obj)
	{
		ForwardList::pushFront(obj);
	}

	void push(ValueType &&obj)
	{
		ForwardList::pushFront(std::move(obj));
	}

	void pop()
	{
		ForwardList::popFront();
	}

	ValueType &top()
	{
		return ForwardList::front();
	}

	const ValueType &top() const
	{
		return ForwardList::front();
	}

	auto size() const
	{
		return ForwardList::size();
	}
};

	/* 使用VECTOR实现单链表 */
//template <typename Object>
//class stack :protected zyvector<Object>
//{
//public:
//	typedef typename Object ValueType;
//	//using zyvector::zyvector;
//	stack(int pos = -1)
//		:topOfStack(-pos)
//	{}
//
//	stack(const stack&oth)
//		:topOfStack(oth.topOfStack), zyvector(oth)
//	{}
//
//	stack(stack &&oth)
//		:topOfStack(oth.topOfStack), zyvector(std::move(oth))
//	{}
//
//	stack(const std::initializer_list<ValueType> &args)
//		:zyvector(args), topOfStack(args.size() - 1)
//	{}
//
//
//	void push(const ValueType &obj)
//	{
//		++topOfStack;
//		if (topOfStack < zyvector::size())
//		{
//			zyvector::operator[](topOfStack) = obj;
//		}
//		else
//		{
//			zyvector::push_back(obj);
//		}
//	}
//
//	void push(ValueType &&obj)
//	{
//		++topOfStack;
//		if (topOfStack < zyvector::size())
//		{
//			zyvector::operator[](topOfStack) = std::move(obj);
//		}
//		else
//		{
//			zyvector::push_back(std::move(obj));
//		}
//	}
//
//	void pop()
//	{
//		//zyvector::pop_back();
//		--topOfStack;
//	}
//
//	ValueType &top()
//	{
//		return zyvector::operator[](topOfStack);
//	}
//
//	const ValueType &top() const 
//	{
//		return zyvector::operator[](topOfStack);
//	}
//
//	int size() const
//	{
//		return topOfStack + 1;
//	}
//private:
//	int topOfStack = -1;
//};
}
#endif