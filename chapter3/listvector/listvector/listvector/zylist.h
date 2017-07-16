#pragma once
#ifndef ZYLIST_H_
#define ZYLIST_H_
#include <cstdbool>
#include <initializer_list>
#include <stdexcept>
/* list链表
 * iterator const_iterator node list四个模板类
 */

namespace zy {
template <typename Object>
class list
{
	typedef typename Object ValueType;
	typedef size_t SizeType;
private:
	class node
	{
	public:
		node(const ValueType &d = ValueType{}, node *pre = nullptr, node *nxt = nullptr)
			:data(d), prev(pre), next(nxt)
		{}

		node(const node &oth)
			:data(oth.data), prev(oth.prev), next(oth.next)
		{}
		node(node &&oth)
			:data(std::move(oth.data)), prev(oth.prev), next(oth.next)
		{
			oth.prev = nullptr;
			oth.next = nullptr;
		}
		node(ValueType &&d, node *pre = nullptr, node *nxt = nullptr)
			:data(std::move(d)), prev(pre), next(nxt)
		{}

	public:
		node *prev;
		node *next;
		ValueType data;
		//friend class list<ValueType>;
	};
public:
	class const_iterator
	{
	public:
		const_iterator()
			:current(nullptr)
		{}

		const_iterator(const_iterator &oth)
			:current(oth.current)
		{}

		const_iterator &operator=(const_iterator &oth)
		{
			current = oth.current;
			return *this;
		}

		const ValueType &operator*() const
		{
			return retrieve();
		}

		const_iterator &operator++()
		{
			current = current->next;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator ret = *this;
			current = current->next;
			return ret;
		}

		const_iterator &operator--()
		{
			current = current->prev;
			return *this;
		}

		const_iterator operator--(int)
		{
			const_iterator ret = *this;
			current = current->prev;
			return ret;
		}

		bool operator==(const const_iterator &rht) const
		{
			return current == rht.current;
		}

		bool operator!=(const const_iterator &rht) const
		{
			return !(*this == rht);
		}
	protected:
		const_iterator(node *p)
			:current(p)
		{}

		ValueType &retrieve() const
		{
			return current->data;
		}
	protected:
		node *current;
		friend class list<ValueType>;
	};

	class iterator :public const_iterator
	{
	public:
		iterator()
		{}

		iterator(const iterator &oth)
			:const_iterator(oth.current)
		{}

		iterator &operator=(const iterator &oth)
		{
			//current = oth.current;
			const_iterator = oth.const_iterator;
		}

		ValueType &operator*()
		{
			return const_iterator::retrieve();
		}

		iterator &operator++()
		{
			current = current->next;
			return *this;
		}

		iterator operator++(int)
		{
			auto ret = *this;
			current = current->next;
			return ret;
		}

		iterator &operator--()
		{
			current = current->prev;
			return *this;
		}

		iterator operator--(int)
		{
			auto ret = *this;
			current = current->prev;
			return ret;
		}
	protected:
		iterator(node *p)
			:const_iterator(p)
		{}
		friend class list<ValueType>;
	};
public:
	list()
	{
		init();
	}

	list(const list &oth)
	{
		init();
		for (const auto &i : oth)
		{
			insertBefore(tail, i);
		}
	}

	list(list &&oth)
		:head(oth.head), tail(oth.tail), theSize(oth.theSize)
	{
		oth.head = nullptr;
		oth.tail = nullptr;
		oth.theSize = 0;
	}

	list(const std::initializer_list<ValueType> &li)
	{
		init();
		for (const auto &i : li)
		{
			insertBefore(tail, i);
		}
	}

	~list()
	{
		clear();
		delete head;
		delete tail;
	}

	list &operator=(const list &oth)
	{
		clear();
		for (const auto &i : oth)
		{
			insertBefore(tail, i);
		}
		return *this;
	}

	list &operator=(list &&oth)
	{
		swap(*this, oth);
	}

	void clear()
	{
		while (!empty())
		{
			deleteNode(tail->prev);
		}
	}

	SizeType size() const
	{
		return theSize;
	}

	bool empty() const
	{
		return theSize == 0;
	}

	iterator begin()
	{
		return head->next;
	}

	const_iterator begin() const
	{
		return head->next;
	}

	iterator end()
	{
		return tail;
	}

	const_iterator end() const
	{
		return tail;
	}

	bool operator==(const list &oth) const
	{
		return (head == oth.head) && (tail == oth.tail);
	}

	bool operator!=(const list &oth) const
	{
		return !(this->operator==(oth));
	}

	ValueType &front()
	{
		if (!empty())
		{
			return *begin();
		}
		else
		{
			throw std::range_error("List is EMPTY");
		}
	}

	const ValueType &front() const
	{
		if (!empty())
		{
			return *begin();
		}
		else
		{
			throw std::range_error("List is EMPTY");
		}
	}

	ValueType &back()
	{
		if (!empty())
		{
			return *(--end());
		}
		else
		{
			throw std::range_error("List is EMPTY");
		}
	}

	ValueType &back() const
	{
		if (!empty())
		{
			return *(--end());
		}
		else
		{
			throw std::range_error("List is EMPTY");
		}
	}

	iterator insert(iterator itr, const ValueType &obj)
	{
		return insertAfter(itr.current, obj);
	}

	iterator insert(iterator itr, ValueType &&obj)
	{
		return insertAfter(itr.current, obj);
	}

	void push_front(const ValueType &obj)
	{
		insertAfter(head, obj);
	}

	void push_front(ValueType &&obj)
	{
		insertAfter(head, obj);
	}

	void push_back(const ValueType &obj)
	{
		insertBefore(tail, obj);
	}

	void push_back(ValueType &&obj)
	{
		insertBefore(tail, obj);
	}

	iterator erase(iterator itr)
	{
		return deleteNode(itr.current);
	}

	/* 删除[from, to)区间 */
	iterator erase(iterator from, iterator to)
	{
		while (from != to)
		{
			from = erase(from);
		}
		return to;
	}

	void pop_front()
	{
		if (!empty())
		{
			erase(begin());
		}
		else
		{
			throw std::range_error("List is EMPTY");
		}
	}

	void pop_back()
	{
		if (!empty())
		{
			erase(--end());
		}
		else
		{
			throw std::range_error("List is empty");
		}
	}

private:
	void init(void)
	{
		head = new node;
		tail = new node;
		head->next = tail;
		tail->prev = head;
		theSize = 0;
	}

	node *insertAfter(node *cur, const ValueType &item)
	{
		node *elem = new node(item, cur, cur->next);
		cur->next->prev = elem;
		cur->next = elem;
		++theSize;
		return elem;
	}

	node *insertAfter(node *cur, ValueType &&item)
	{
		node *elem = new node(std::move(item), cur, cur->next);
		cur->next->prev = elem;
		cur->next = elem;
		++theSize;
		return elem;
	}

	node *insertBefore(node *cur, const ValueType &item)
	{
		return insertAfter(cur->prev, item);
	}

	node *insertBefore(node *cur, ValueType &&item)
	{
		return insertAfter(cur->prev, item);
	}

	node *deleteNode(node *cur)
	{
		auto ret = cur->next;
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		delete cur;
		--theSize;
		return ret;
	}

	friend void swap(list &lft, list &rht)
	{
		using std::swap;
		if (lft != rht)
		{
			swap(lft.head, lft.head);
			swap(lft.tail, rht.tail);
			swap(lft.theSize, lft.theSize);
		}
	}
private:
		node *head;
		node *tail;
		SizeType theSize;
};
	
}
#endif