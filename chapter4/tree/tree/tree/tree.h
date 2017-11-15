#pragma once
#ifndef TREE_H_
#define TREE_H_

#include <utility>
#include <iostream>
#include <random>
#include <time.h>

namespace zy {
template<typename Object>
class Tree
{
public:
    typedef typename Object ValueType;
    typedef size_t SizeType;
protected:
    class Node
    {
    public:
        Node(const ValueType &item = ValueType{}, Node *child = nullptr, Node *sibling = nullptr)
            :data(item), firstChild(child), nextSibling(sibling)
        {}
        Node(const Node &oth)
            :data(oth.data), firstChild(nullptr), nextSibling(nullptr)
        {}
        Node(Node &&oth) noexcept
            :data(std::move(oth.data)), firstChild(nullptr), nextSibling(nullptr)
        {
            oth.nextSibling = nullptr;
            oth.firstChild = nullptr;
        }

        Node &operator=(const Node &oth)
        {
            data = oth.data;
            firstChild = oth.firstChild;
            nextSibling = oth.nextSibling;
            return *this;
        }

        Node &operator=(Node &&oth)
        {
            data = std::move(oth.data);
            firstChild = std::move(oth.firstChild);
            nextSibling = std::move(oth.nextSibling);
            
            oth.firstChild = nullptr;
            oth.nextSibling = nullptr;
            return *this;

        }

      /*  friend void swap(Node &lft, Node &rht)
        {
            using std::swap;
            swap(lft.data, rht.data);
            swap(lft.firstChild, rht.firstChild);
            swap(lft.nextSibling, rht.nextSibling);
        }*/
    public:
        ValueType data;
        Node *firstChild;
        Node *nextSibling;
    };
public:
    Tree()
        :root(nullptr)
    {}
    Tree(const Tree &oth)
        :Tree()
    {
        //拷贝构造oth的整个树,递归遍历构造
        TraversalTreeToConstructTree(oth.root, &root);
    }
    Tree(Tree &&oth)
        :root(std::move(oth.root))
    {
        oth.root = nullptr;
    }

    ~Tree()
    {
        //递归析构
        DestructTree(root);
    }

    Tree &operator=(Tree oth)
    {
        swap(*this, oth);
        return *this;
    }

    void insert(ValueType &item)
    {
        std::default_random_engine e;//(static_cast<unsigned int>time(NULL));
        std::bernoulli_distribution b;
        if (!root)
        { 
            root = new Node(item);
        }
        else
        {
            InsertRecursive(root, item, e, b);
        }
    }

    void PreorderTraversal(std::ostream &out, SizeType depth = 0)
    {
        PreorderRecursive(root, out, depth);
    }

    void PostorderTraversal(std::ostream &out, SizeType depth = 0)
    {
        PostorderRecursive(root, out, depth);
    }
private:
    void InsertRecursive(Node *nd, ValueType &item, std::default_random_engine &e, std::bernoulli_distribution &b)
    {
        bool child = b(e);
        if (child)
        {
            if (!nd->firstChild)
            {
                nd->firstChild = new Node(item);
            }
            else
            {
                InsertRecursive(nd->firstChild, item, e, b);
            }
        }
        else
        {
            if (!nd->nextSibling)
            {
                nd->nextSibling = new Node(item);
            }
            else
            {
                InsertRecursive(nd->nextSibling, item, e, b);
            }
        }
    }

    void PreorderRecursive(const Node *nd, std::ostream &out, SizeType depth)
    {
        if (nd)
        {
            VisitNode(nd, out, depth);
            PreorderRecursive(nd->firstChild, out, depth + 1);
            PreorderRecursive(nd->nextSibling, out, depth);
        }
    }

    void PostorderRecursive(const Node *nd, std::ostream &out, SizeType depth)
    {
        if (nd)
        {
            PostorderRecursive(nd->firstChild, out, depth + 1);
            PostorderRecursive(nd->nextSibling, out, depth);
            VisitNode(nd, out, depth);
        }
    }

    void VisitNode(const Node *nd, std::ostream &out, SizeType depth)
    {
        if (nd)
        {
            while (depth)
            {
                out << ' ';
                --depth;
            }
            out << nd->data << std::endl;
        }
    }

    void DestructTree(Node *nd)
    {
        if (!nd)
        {
            return;
        }
        //定义两个中间变量是为了实现尾递归优化
        Node *firstChild = nd->firstChild;
        Node *nextSibling = nd->nextSibling;
        delete nd;
        DestructTree(firstChild);
        DestructTree(nextSibling);
    }

    void TraversalTreeToConstructTree(const Node *source, Node **dest)
    {
        if (!source)
        {
            *dest = nullptr;
            return;
        }
        else
        {
            *dest = new Node(*source);
        }
        if (source->firstChild)
        {
            TraversalTreeToConstructTree(source->firstChild, &((*dest)->firstChild));
        }
        else if (source->nextSibling)
        {
            TraversalTreeToConstructTree(source->nextSibling, &((*dest)->nextSibling));
        }
    }
    friend void swap(Tree &lft, Tree &rht)
    {
        using std::swap;
        swap(lft.root, rht.root);
    }
private:
    Node *root;
};
}

#endif
