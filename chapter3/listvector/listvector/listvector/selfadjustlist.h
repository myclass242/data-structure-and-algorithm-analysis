#pragma once
#ifndef SELFADJUSTLIST_H_
#define SELFADJUSTLIST_H_
#include <memory>
#include <stdexcept>
#include <exception>
#include <initializer_list>

/*
 * 1.每个节点增加一个指示节点是否有效的变量，实现链表删除某个节点，原先指向该节点的迭代器失效的功能
 * 使用智能指针shared_ptr实现表示节点是否有效的变量：
 * 节点有效则shared_ptr指向的内存的值为1，在节点析构时把shared_ptr指向的内存的值置为0
 * 2.迭代器包含一个指向迭代器所工作的链表的指针，用于判断迭代器是否在正确的链表上工作
 */
namespace zy {
template<typename Object>
class SelfAdjustList
{
    typedef typename Object ValueType;
    typedef size_t SizeType;
protected:
    class node
    {
    public:
        node(const ValueType &d = ValueType{}, node *nxt = nullptr)
            :item(d), next(nxt)
        {
            nodeValid = std::make_shared<int>(1);
        }

        node(const node &oth) = delete;
        //    :item(oth.item), next(oth.next), nodeValid(oth.nodeValid)
        //{}

        node(node &&oth) = delete;
        //    :item(std::move(oth.item)), next(next), nodeValid(oth.nodeValid)
        //{
        //    oth.next = nullptr;
        //    oth.nodeValid = nullptr;
        //}

        node(ValueType &&d, const node *nxt = nullptr)
            :item(std::move(d)), next(nxt)
        {
            nodeValid = std::make_shared<int>(1);
        }

        ~node()
        {
            *nodeValid = 0;
        }
    public:
        ValueType item;
        node *next;
        std::shared_ptr<int> nodeValid;
    };
public:
    class const_iterator
    {
    public:
        const_iterator()
            :current(nullptr), nodeValid(nullptr), lst(nullptr)
        {}
        const_iterator(const const_iterator &oth)
            :nodeValid(oth.nodeValid), current(oth.current),  lst(oth.lst)
        {
            //nodeValid = oth.nodeValid;
        }

        const_iterator(const_iterator &&oth)
            :current(std::move(oth.current)),
            nodeValid(std::move(oth.nodeValid)),
            lst(std::move(oth.lst))
        {
            oth.current = nullptr;
            oth.nodeValid = nullptr;
            oth.lst = nullptr;
        }
    
        const_iterator &operator=(const const_iterator &oth)
        {
            current = oth.current;
            nodeValid = oth.nodeValid;
            lst = oth.lst;
            //swap(*this, oth);
            return *this;
        }

        const_iterator &operator++(void)
        {
            current = current->next;
            syncNodeValid();
            return *this;
        }

        const_iterator operator++(int)
        {
            auto ret = *this;
            ++(*this);
            return ret;
        }

        const ValueType &operator*() const
        {
            return retrieve();
        }

        bool operator==(const const_iterator &oth) const
        {
            return current == oth.current;
        }

        bool operator!=(const const_iterator &oth) const
        {
            return !(*this == oth);
        }
    private:
        /*friend void swap(const_iterator &lft, const_iterator &rht)
        {
            using std::swap;
            swap(lft.current, rht.current);
            swap(lft.nodeValid, rht.nodeValid);
            swap(lft.lst, rht.lst);
        }*/

        void syncNodeValid(void)
        {
            if (current)
            {
                nodeValid = current->nodeValid;
            }
            else
            {
                nodeValid = nullptr;
            }
        }

        bool iteratorValid(void) const
        {
            bool ret = false;
            if (0 != *nodeValid)
            {
                ret = true;
            }
            return ret;
        }

        void checkIterator(void) const
        {
            if (lst == nullptr || current == nullptr)
            {
                throw std::exception("迭代器无效或指向无效数据");
            }
        }
    protected:
        const_iterator(node *pNode, const SelfAdjustList *link)
            :current(pNode), lst(const_cast<SelfAdjustList *>(link))
        {
            if (nullptr != pNode)
            {
                nodeValid = pNode->nodeValid;
            }
            else
            {
                nodeValid = nullptr;
            }
        }

        ValueType &retrieve(void) const
        {
            if (!iteratorValid())
            {
                throw std::exception("迭代器指向内存无效");
            }
            checkIterator();
            return current->item;
        }
        friend SelfAdjustList<ValueType>;
    protected:
        node *current;
        std::shared_ptr<int> nodeValid;
        SelfAdjustList *lst;
    };
    class iterator :public const_iterator
    {
    public:
        using const_iterator::const_iterator; //使用基类的构造函数
        iterator &operator=(const iterator &oth)
        {
            const_iterator::operator=(oth);
            return *this;
        }

        iterator &operator++(void)
        {
            const_iterator::operator++();
            return *this;
        }

        iterator operator++(int)
        {
            auto ret = *this;
            ++(*this);
            return ret;
        }

        ValueType &operator*(void)
        {
            //return const_cast<ValueType>(const_iterator::operator*());
            //return const_iterator::operator*();
            return const_iterator::retrieve();
        }

        const ValueType &operator*(void) const
        {
            return const_iterator::operator*();
        }

        bool operator==(const iterator &oth) const
        {
            return const_iterator::operator==(oth);
        }

        bool operator!=(const iterator &oth) const
        {
            return !(*this == oth);
        }
        friend SelfAdjustList<ValueType>;
    };
public:
    SelfAdjustList()
        :head(nullptr), theSize(0)
    {}

    SelfAdjustList(const SelfAdjustList &oth)
        :SelfAdjustList()
    {
        for (const auto &data : oth)
        {
            push_front(data);
        }
    }

    SelfAdjustList(SelfAdjustList &&oth)
        :head(oth.head), theSize(oth.theSize)
    {
        oth.head = nullptr;
        oth.theSize = 0;
    }

    SelfAdjustList(const std::initializer_list<ValueType> &li)
        :SelfAdjustList()
    {
        for (const auto &data : li)
        {
            push_front(data);
        }
    }

    ~SelfAdjustList()
    {
        while (head)
        {
            node *lastNode = head;
            head = head->next;
            delete lastNode;
        }
    }

    SelfAdjustList &operator=(SelfAdjustList rlt)
    {
        swap(*this, rlt);
        return *this;
    }

    const_iterator begin() const
    {
        return const_iterator(head, this);
    }

    iterator begin()
    {
        return iterator(head, this);
    }

    const_iterator end() const
    {
        return const_iterator(nullptr, this);
    }

    iterator end()
    {
        return iterator(nullptr, this);
    }

    SizeType size() const
    {
        return theSize;
    }

    bool empty() const
    {
        return 0 == theSize;
    }

    void pop_front()
    {
        if (!empty())
        {
            node *waste = head;
            head = head->next;
            --theSize;
            delete waste;
        }
    }

    iterator insert(const iterator &ite, const ValueType &item)
    {
        ite.checkIterator();
        if (ite.lst != this)
        {
            throw std::exception("迭代器不匹配");
        }
        node *newNode = new node(item, ite.current->next);
        ite.current->next = newNode;
        ++theSize;
        return iterator(newNode, this);
    }

    void push_front(const ValueType &data)
    {
        node *newNode = new node(data, head);
        head = newNode;
        ++theSize;
    }

    void find(const ValueType &data)
    {
        node *parentNode = findParentPosition(data);
        if (parentNode)
        {
            node *moveaheadNode = parentNode->next;
            parentNode->next = moveaheadNode->next;
            moveaheadNode->next = head;
            head = moveaheadNode;
        }
    }
private:
    node *findParentPosition(const ValueType &data)
    {
        node *currentNode = head;
        node *lastNode = nullptr;
        while (currentNode && data != currentNode->item)
        {
            lastNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode)
        {
            return lastNode;
        }
        return nullptr;
    }

    friend void swap(SelfAdjustList &lft, SelfAdjustList &rht)
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
#endif
