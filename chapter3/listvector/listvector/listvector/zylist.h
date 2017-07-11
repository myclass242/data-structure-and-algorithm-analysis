#pragma once
#ifndef ZYLIST_H_
#define ZYLIST_H_
#include <cstdbool>
#include <initializer_list>
/* list链表
 * iterator const_iterator node list四个模板类 
 */

namespace zy {

template <typename Object>
class list
{
public:
	typedef typename Object ValueType;
private: /* iterator 和 node 应该为list 类的嵌套类 */
	class node
	{
	public:
		node(const ValueType &d = ValueType{}, node *pre = nullptr, node *nxt = nullptr)
			:data(d), next(nxt), prev(pre)
		{}

		node(ValueType &&d, node *pre = nullptr, node *nxt = nullptr)
			:data(std::move(d)), next(nxt), prev(pre)
		{}

		node(const node &oth)
			:data(oth.data), next(nullptr), prev(nullptr)
		{}

		node(node &&oth)
			:data(std::move(oth.data)), next(oth.next), prev(oth.prev)
		{}
		//friend class list<Object>::iterator;
	public:
		node *next;
		node *prev;
		/*iterator next;
		iterator prev;*/
		ValueType data;
	};
public:
	class const_iterator
	{
		friend class list<Object>;
	public:
		const_iterator()
			:current(nullptr)
		{}


		const ValueType &operator*() const
		{
			return retrieve();
		}

		const node *operator->() const
		{
			return current;
		}

		const_iterator &operator++()
		{
			current = current->next;
			return *this;
		}

		const_iterator operator++(int)
		{
			auto ret = *this;
			++(*this);
			return ret;
		}

		const_iterator &operator--()
		{
			current = current->prev;
			return *this;
		}

		const_iterator operator--(int)
		{
			auto ret = *this;
			--(*this);
			return ret;
		}

		friend bool operator==(const const_iterator &lft, const const_iterator &rht)
		{
			return lft.current == rht.current;
		}

		friend bool operator!=(const const_iterator &lft, const const_iterator &rht)
		{
			return !(lft == rht);
		}

		friend void swap(const_iterator &lft, const_iterator &rht)
		{
			using std::swap;
			swap(lft.current, rht.current);
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
	};
	
	class iterator : public const_iterator
	{
		friend class list<Object>;
	public:
		iterator()
		{}

		ValueType &operator*()
		{
			return const_iterator::retrieve();
		}

		const ValueType &operator*() const
		{
			return const_iterator::retrieve();
		}

		node *operator->()
		{
			return current;
		}

		const node *operator->() const
		{
			return current;
		}

		iterator &operator++()
		{
			current = current->next;
			return *this;
		}

		iterator operator++(int)
		{
			auto ret = *this;
			++(*this);
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
			--(*this);
			return ret;
		}
	protected:
		iterator(node *p)
			:const_iterator{p}
		{}
	};

public:
	list()
	{
		init();
	}

	list(const list &oth)
		:list(), theSize(oth.theSize)
	{
		insertList(oth.head, oth.tail, head, tail);
	}

	list(list &&oth)
		:list()
	{
		swap(*this, oth);
	}

	list(const std::initializer_list<ValueType> &lt)
		:list()
	{
		auto insertPos = begin();
		for (const auto &sur : lt)
		{
			node *obj = new node(sur);
			insertPos = insertAfterIterator(insertPos, *obj);
			++theSize;
		}
	}

	~list()
	{
		destory(begin(), end());
		delete head;
		delete tail;
	}

	list &operator=(const list &oth)
	{
		destory(begin(), end());
		insertList(oth.head, oth.tail, head, tail);
		theSize = oth.theSize;
	}

	iterator &insert(iterator &pos, ValueType item)
	{
		node obj = new node(std::move(item));
		++theSize;
		return insertAfterIterator(pos, obj);
		
	}

	iterator &erase(iterator &pos)
	{
		auto ret = pos->prev;
		destory(pos, pos);
		return ret;
	}

	iterator &erase(iterator &begin, iterator &end)
	{
		auto ret = begin->prev;
		destory(begin, end);
		return ret;
	}

	bool empty() const
	{
		return theSize == 0;
	}

	iterator &begin()
	{
		return static_cast<iterator>(head->next);
	}

	const_iterator &begin() const
	{
		return static_cast<const_iterator>(head->next);
	}

	const_iterator &end() const
	{
		if (!empty())
		{
			return static_cast<const_iterator>(tail->prev);
		}
		return static_cast<const_iterator>(tail);
	}

	iterator &end()
	{
		if (!empty())
		{
			return static_cast<iterator>(tail->prev);
		}
		return static_cast<iterator>(tail);
	}

private:
	void init(void)
	{
		theSize = 0;
		head = new node;
		tail = new node;
		head->next = tail;
		tail->prev = head;
	}

	iterator &insertAfterIterator(iterator &cur, node &obj)
	{
		auto tmp = cur->next;
		cur->next->prev = &obj;
		cur->next = &obj;
		obj.next = tmp;
		obj.prev = cur.current;
		return iterator(&obj);
	}

	void insertList(iterator &outBegin, iterator &outEnd, iterator &inBegin, iterator &inEnd)
	{
		iterator traversalOthList = outBegin->next;
		iterator traversalThisList = inBegin;
		while (traversalOthList != outEnd)
		{
			node *tmp = new node(*traversalOthList);
			//insertAfterNode(traversalThisList, *tmp);
			insertAfterIterator(traversalThisList, *tmp);
			++traversalThisList;
			++traversalOthList;
		}
	}

	void destory(iterator &begin, iterator &end)
	{
		if (empty())
		{
			return;
		}
		begin->prev->next = end->next;
		end->next->prev = begin->prev;
		auto cur = begin;
		while (cur != end)
		{
			auto nxt = cur->next;
			delete cur.current;
			cur = nxt;
			--theSize;
		}
		delete cur.current;
		--theSize;
	}

	friend void swap(list &lft, list &rht)
	{
		using std::swap;
		swap(lft.head, rht.head);
		swap(lft.tail, rht.tail);
		swap(lft.theSize, rht.theSize);
	}
private:
	node *head;
	node *tail;
	size_t theSize;
};

//template<typename Object>
//class list<Object>::node
//{
//public:
//	node(const ValueType &d = ValueType{}, node *pre = nullptr, node *nxt = nullptr)
//		:data(d), next(nxt), prev(pre)
//	{}
//
//	node(ValueType &&d, node *pre = nullptr, node *nxt = nullptr)
//		:data(std::move(d)), next(nxt), prev(pre)
//	{}
//
//	node(const node &oth)
//		:data(oth.data), next(nullptr), prev(nullptr)
//	{}
//
//	node(node &&oth)
//		:data(std::move(oth.data)), next(oth.next), prev(oth.prev)
//	{}
//	//friend class list<Object>::iterator;
//public:
//	/*node *next;
//	node *prev;*/
//	iterator next;
//	iterator prev;
//	ValueType data;
//};
//
//template<typename Object>
//class list<Object>::const_iterator
//{
//	friend class list<Object>;
//public:
//	const_iterator()
//		:current(nullptr)
//	{}
//
//
//	const ValueType &operator*() const
//	{
//		return retrieve();
//	}
//
//	const ValueTypr *operator->() const
//	{
//		return &this->operator*();
//	}
//
//	const_iterator &operator++()
//	{
//		current = current->next;
//		return *this;
//	}
//
//	const_iterator operator++(int)
//	{
//		auto ret = *this;
//		++(*this);
//		return ret;
//	}
//
//	const_iterator &operator--()
//	{
//		current = current->prev;
//		return *this;
//	}
//
//	const_iterator operator--(int)
//	{
//		auto ret = *this;
//		--(*this);
//		return ret;
//	}
//
//	friend bool operator==(const const_iterator &lft, const const_iterator &rht) 
//	{
//		return lft.current == rht.current;
//	}
//
//	friend bool operator!=(const const_iterator &lft, const const_iterator &rht) 
//	{
//		return !(lft == rht);
//	}
//
//	friend void swap(const_iterator &lft, const_iterator &rht)
//	{
//		using std::swap;
//		swap(lft.current, rht.current);
//	}
//protected:
//	const_iterator(node *p)
//		:current(p)
//	{}
//
//	ValueType &retrieve() const
//	{
//		return current->data;
//	}
//protected:
//	node *current;
//};

//template <typename Object>
//class list<Object>::iterator:public const_iterator
//{
//	friend class list<Object>;
//public:
//	iterator()
//	{}
//
//	ValueType &operator*()
//	{
//		return const_iterator::retrieve();
//	}
//
//	const ValueType &operator*() const
//	{
//		return const_iterator::retrieve();
//	}
//
//	ValueType *operator->()
//	{
//		return &this->operator*();
//	}
//
//	const ValueType *operator->() const
//	{
//		return &this->operator*();
//	}
//
//	iterator &operator++()
//	{
//		current = current->next;
//		return *this;
//	}
//
//	iterator operator++(int)
//	{
//		auto ret = *this;
//		++(*this);
//		return ret;
//	}
//
//	iterator &operator--()
//	{
//		current = current->prev;
//		return *this;
//	}
//
//	iterator operator--(int)
//	{
//		auto ret = *this;
//		--(*this);
//		return ret;
//	}
//protected:
//	iterator(node *p)
//		:current(p)
//	{}
//};
}
#endif