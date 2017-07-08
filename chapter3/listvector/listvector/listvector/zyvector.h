#pragma once
#ifndef ZYVECTOR_H_
#define ZYVECTOR_H_
#include <memory>
#include <cstdbool>

/* 类似STL vector的实现 */
namespace zy {
template <typename Object>
class zyvector
{
public:
	typedef typename Object ValueType;
	typedef size_t SizeType;
	typedef ValueType * iterator;
	typedef const ValueType * ConstIterator;
public:
	explicit zyvector(SizeType num = 0)
		: theSize(num)
	{
		if (theSize == 0)
		{
			theCapacity = SPARE_CAPACITY;
		}
		else
		{
			theCapacity = INCREASE_TIMES * theSize;
		}
		data = allocat_n(theCapacity);
		std::uninitialized_fill_n(data, theSize, ValueType{});
	}

	zyvector(const zyvector &oth)
		:theSize(oth.theSize),theCapacity(oth.theCapacity)
	{
		data = allocat_n(theCapacity);
		std::uninitialized_copy(oth.cbegin(), oth.cend(), begin());
	}

	zyvector(zyvector &&oth)
		:data(nullptr),theSize(0),theCapacity(0)
	{
		swap(*this, oth);
	}

	zyvector(const std::initializer_list<ValueType> &args)
		:theSize(args.size()),theCapacity(INCREASE_TIMES * args.size())
	{
		data = allocat_n(theCapacity);
		std::uninitialized_copy(args.begin(), args.end(), data);
	}

	/*zyvector(std::initializer_list<ValueType> &&args)
		:theSize(args.size()), theCapacity(INCREASE_TIMES * args.size())
	{
		data = allocat_n(theCapacity);
		move_n(args.begin(), theSize, data);
	}*/

	~zyvector()
	{
		destory_n(data, theSize);
		deallocat_n(data, theCapacity);
	}

	zyvector &operator=(zyvector rht)
	{
		swap(*this, rht);
		return *this;
	}

	ValueType &operator[](SizeType pos)
	{
		return *(data + pos);
	}

	const ValueType &operator[](SizeType pos) const
	{
		return *(data + pos);
	}

	SizeType size() const
	{
		return theSize;
	}

	SizeType capacity() const
	{
		return theCapacity;
	}

	bool empty() const
	{
		return theSize == 0;
	}

	void clear()
	{
		destory_n(data, theSize);
		theSize = 0;
	}

	void reserve(SizeType newCapacity)
	{
		if (newCapacity < theCapacity)
		{
			ValueType *newData = allocat_n(newCapacity);
			//std::uninitialized_copy_n(begin(), newCapacity, newData);
			SizeType copyConstructNums = theSize < newCapacity ? theSize : newCapacity;
			//std::uninitialized_copy_n(begin(), copyConstructNums, newData);
			move_n(begin(), copyConstructNums, newData);
			destory_n(data, theSize);
			deallocat_n(data, theCapacity);
			/*if (theSize > newCapacity)
			{
				theSize = newCapacity;
			}*/
			theSize = copyConstructNums;
			data = newData;
		}
		else if(theCapacity < newCapacity)
		{
			increase_n(newCapacity);
		}
		theCapacity = newCapacity;
	}

	void resize(SizeType newSize)
	{
		if (newSize > theCapacity)
		{
			increase_n(INCREASE_TIMES * newSize);
			std::uninitialized_fill_n(begin() + theSize, newSize - theSize, ValueType{});
			theCapacity = INCREASE_TIMES * newSize;
		}
		else
		{
			if (newSize > theSize)
			{
				std::uninitialized_fill_n(begin() + theSize, newSize - theSize, ValueType{});
			}
			else
			{
				destory_n(begin() + newSize, theSize - newSize);
			}
		}
		theSize = newSize;
	}

	iterator begin() 
	{
		return data;
	}

	ConstIterator begin() const
	{
		return data;
	}

	ConstIterator cbegin() const
	{
		return begin();
	}

	iterator end()
	{
		return data + theSize;
	}

	ConstIterator end() const
	{
		return data + theSize;
	}

	ConstIterator cend() const
	{
		return end();
	}

	ValueType &back()
	{
		return *(end() - 1);
	}

	const ValueType &back() const
	{
		return *(end() - 1);
	}

	ValueType &pop()
	{
		return *(begin());
	}

	const ValueType &pop() const
	{
		return *(begin());
	}

	void push_back(const ValueType &item)
	{
		if (theSize == theCapacity)
		{
			reserve(INCREASE_TIMES * theCapacity);
		}
		alloc.construct(end(), item);
		++theSize;	
	}

	void pop_back()
	{
		alloc.destroy(end() - 1);
		--theSize;
	}
private:
	friend void swap(zyvector &lft, zyvector &rht)
	{
		using std::swap;
		swap(lft.data, rht.data);
		swap(lft.theSize, rht.theSize);
		swap(lft.theCapacity, rht.theCapacity);
	}

	ValueType *allocat_n(SizeType n)
	{
		return alloc.allocate(n);
	}

	void destory_n(ValueType *pos,SizeType n)
	{
		for (SizeType i = 0; i != n; ++i)
		{
			alloc.destroy(pos + i);
			//alloc.destructor(pos + i);
		}
	}

	//void move_n(iterator input, SizeType nums, iterator dest)
	void move_n(ValueType *input, SizeType nums, ValueType *dest)
	{
		for (SizeType i = 0; i != nums; ++i)
		{
			dest[i] = std::move(input[i]);
		}
	}

	void deallocat_n(ValueType *pos,SizeType n)
	{
		alloc.deallocate(pos, n);
	}

	ValueType *increase_n(SizeType bigSize/*, SizeType moveSize = 0*/)
	{
		/*if (moveSize == 0)
		{
			moveSize = bigSize;
		}*/
		ValueType *newData = allocat_n(bigSize);
		//std::uninitialized_copy(begin(), end(), newData);
		move_n(begin(), theSize, newData);
		destory_n(data, theSize);
		deallocat_n(data, theCapacity);
		data = newData;
		return data;
	}
private:
	std::allocator<ValueType> alloc;	/* 内存分配方法，分配非初始化对象 */
private:
	ValueType *data;
	SizeType theSize;		/* 元素数量 */
	SizeType theCapacity; /* 容量 */
	static const SizeType SPARE_CAPACITY = 100;
	static const SizeType INCREASE_TIMES = 2;
};

}
#endif