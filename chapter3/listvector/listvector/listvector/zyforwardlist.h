#pragma once
#ifndef ZYFORWARDLIST_H_
#define ZYFORWARELIST_H_
#include <cstdbool>
#include <initializer_list>
namespace zy {
template <typename Object>
class ForwardList
{
	typedef typename Object ValueType;
	typedef size_t SizeType;
private:
	class node
	{
	public:
		node(const ValueType &d = ValueType{}, node *nxt = nullptr)
			:data(d), next(nxt)
		{}

		node(ValueType &&d, node *nxt = nullptr)
			:data(std::move(d)), next(nxt)
		{}

		node(const node &oth)
			:data(oth.data), next(oth.next)
		{}

		node(node &&oth)
			:data(std::move(oth.data)), next(oth.next)
		{
			oth.next = nullptr;
			//oth.data = ValueType{};
		}
	public:
		ValueType data;
		node *next;
	};
public:
	class const_iterator
	{
	public:
		const_iterator()
			:current(nullptr), thisList(nullptr)
		{}

		const_iterator(const const_iterator &oth)
			:current(oth.current), thisList(oth.thisList)
		{}

		/*const_iterator(const iterator &oth)
			:current(oth.current), thisList(oth.thisList)
		{}*/

		const ValueType &operator*() const
		{
			return retrieve();
		}

		/*const_iterator &operator=(const const_iterator &oth)
		{
			current = oth.current;
			thisList = oth.thisList;
			return *this;
		}*/

		bool operator==(const const_iterator &oth) const
		{
			return (current == oth.current) && (thisList == oth.thisList);
		}

		bool operator!=(const const_iterator &oth) const
		{
			return !(*this == oth);
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
	protected:
		const ValueType &retrieve() const
		{
			return current->data;
		}

		const_iterator(node *p ,const ForwardList *const li)
			:current(p) ,thisList(li)
		{}
		friend ForwardList;
	protected:
		node *current;
		const ForwardList *const thisList;
	};
	class iterator :public const_iterator
	{
	public:
		iterator()
		{}

		iterator(const iterator &oth)
			:const_iterator(oth.current, oth.thisList)
		{}

		ValueType &operator*()
		{
			return const_iterator::retrieve();
		}

		/*iterator &operator=(const iterator &oth)
		{
			const_iterator = oth.const_iterator;
		}*/

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

		bool operator==(const iterator &oth) const
		{
			return (current == oth.current) && (thisList == oth.thisList);
		}

		bool operator!=(const iterator &oth) const
		{
			return !(*this == oth);
		}
	protected:
		iterator(node *p, const ForwardList *const li)
			:const_iterator(p, li)
		{}
		friend ForwardList;
	};
public:
	ForwardList()
	{
		init();
	}
	
	ForwardList(const ForwardList &oth)
	{
		init();
		node *insertPos = head;
		for (const auto &i : oth)
		{
			insertPos = insertAfter(insertPos, i);
		}
	}

	ForwardList(ForwardList &&oth)
		:head(oth.head), theSize(oth.theSize)
	{
		oth.head = nullptr;
		oth.theSize = 0;
	}

	ForwardList(const std::initializer_list<ValueType> &li)
	{
		init();
		node *insertPos = head;
		for (const auto &i : li)
		{
			insertPos = insertAfter(insertPos, i);
		}
	}

	~ForwardList()
	{
		clearList();
		delete head;
	}

	ForwardList &operator=(ForwardList oth)
	{
		swap(*this, oth);
		return *this;
	}

	iterator begin()
	{
		return iterator(head->next, this);
	}

	const_iterator begin() const
	{
		return const_iterator(head->next, this);
	}

	iterator BeforeBegin()
	{
		return iterator(head, this);
	}

	const_iterator BeforeBegin() const
	{
		return const_iterator(head, this);
	}

	iterator end()
	{
		return iterator(findEnd(), this);
	}

	const_iterator end() const
	{
		auto nd = findEnd();
		return const_iterator(const_cast<node *>(nd), this);
	}

	void clear()
	{
		clearList();
	}

	SizeType size() const
	{
		return theSize;
	}

	bool empty() const
	{
		return theSize == 0;
	}

	void pushFront(const ValueType &obj)
	{
		insertAfter(head, obj);
	}

	void pushFront( ValueType &&obj)
	{
		insertAfter(head, std::move(obj));
	}

	void popFront()
	{
		deleteNodeAfter(head);
	}

	ValueType &front()
	{
		return head->next->data;
	}

	const ValueType &front() const
	{
		return head->next->data;
	}
private:
	void init()
	{
		head = new node;
		theSize = 0;
	}

	node *insertAfter(node *pos, const ValueType &obj)
	{
		node *tag = new node(obj, pos->next);
		pos->next = tag;
		++theSize;
		return tag;
	}

	bool deleteNodeAfter(node *pos)
	{
		if (pos->next)
		{
			node *deleteTarget = pos->next;
			pos->next = pos->next->next;
			delete deleteTarget;
			--theSize;
			return true;
		}
		return false;
	}

	void clearList()
	{
		while (deleteNodeAfter(head))
		{
			continue;
		}
	}

	const node *findEnd() const
	{
		const node *throughList = head;
		while (throughList->next)
		{
			throughList = throughList->next;
		}
		return throughList;
	}

	node *findEnd()
	{
		return const_cast<node *>((const_cast<const ForwardList>(*this)).findEnd());
	}


	friend void swap(ForwardList &lft, ForwardList &rht)
	{
		using std::swap;
		swap(lft.head, rht.head);
		swap(lft.theSize, rht.theSize);
	}
private:
	node *head;
	SizeType theSize;
};
}
#endif // !ZYFORWARDLIST_H_
