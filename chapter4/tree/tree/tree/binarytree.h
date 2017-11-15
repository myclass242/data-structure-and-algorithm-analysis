#pragma once
#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <cstddef>
#include <utility>
#include <ostream>

namespace zy {
template<typename Object>
class BinaryTree
{
public:
    typedef typename Object ValueType;
    typedef std::size_t SizeType;
protected:
    class Node
    {
    public:
        Node(const ValueType &data = ValueType{})
            :item(data), left(nullptr), right(nullptr)
        {}
        Node(const Node &oth)
            :item(oth.item), left(nullptr), right(nullptr)
        {}
        Node(const Node &&oth) noexcept
            :item(std::move(oth.item)), left(std::move(oth.left)), right(std::move(oth.right))
        {}
        ~Node()
        {
            //do nothing
        }
        Node &operator=(const Node &oth)
        {
            if (&oth != this)
            {
                item = oth.item;
                left = oth.left;
                right = oth.right;
            }
            return *this;
        }
        Node &operator=(Node &&oth) noexcept
        {
            if (&oth != this)
            {
                item = std::move(oth.item);
                left = std::move(oth.left);
                right = std::move(oth.right);
                oth.left = nullptr;
                oth.right = nullptr;
            }
            return *this;
        }
    private:
        friend BinaryTree<ValueType>;
    private:
        ValueType item;
        Node *left;
        Node *right;
    };
public:
    BinaryTree()
        :root(nullptr)
    {}
    BinaryTree(const BinaryTree &oth)
        :BinaryTree()
    {
        CopyConstructTree(oth.root, &root);
    }
    BinaryTree(BinaryTree &&oth) noexcept
        : root(std::move(oth.root))
    {
        oth.root = nullptr;
    }
    explicit BinaryTree(const ValueType &data)
        :root(new Node(data))
    {}

    ~BinaryTree()
    {
        DestoryTree(root);
    }
    BinaryTree &operator=(BinaryTree rht)
    {
        swap(*this, rht);
    }
    void preorderPrint(std::ostream &out) const
    {
        doPreorderPrint(root, out);
        out << std::endl;
    }
    void inorderPrint(std::ostream &out) const
    {
        doIneorderPrint(root, out);
        out << std::endl;
    }
    void postorderPrint(std::ostream &out) const
    {
        doPostorderPrint(root, out);
        out << std::endl;
    }

    void insertLeft(BinaryTree &&lft)
    {
        Node **target = &root;
        while (*target)
        {
            target = &((*target)->left);
        }
        *target = lft.root;
        lft.root = nullptr;
    }

    void insertRight(BinaryTree &&rht)
    {
        Node **target = &root;
        while (*target)
        {
            target = &((*target)->right);
        }
        *target = rht.root;
        rht.root = nullptr;
    }
private:
    void doPreorderPrint(const Node *pnd, std::ostream &out) const
    {
        if (pnd)
        {
            out << pnd->item << " ";
            doPreorderPrint(pnd->left, out);
            doPreorderPrint(pnd->right, out);
        }
    }
    void doIneorderPrint(const Node *pnd, std::ostream &out) const
    {
        if (pnd)
        {
            out << "(" << " ";
            doIneorderPrint(pnd->left, out);
            out << pnd->item << " ";
            doIneorderPrint(pnd->right, out);
            out << ")" << " ";
        }
    }
    void doPostorderPrint(const Node *pnd, std::ostream &out) const
    {
        if (pnd)
        {
            doPostorderPrint(pnd->left, out);
            doPostorderPrint(pnd->right, out);
             out << pnd->item << " ";
        }
    }
    void CopyConstructTree(const Node *source, Node **dest)
    {
        if (source)
        {
            *dest = new Node(*source);
            const Node *lft = source->left;
            const Node *rht = source->right;
            CopyConstructTree(lft, &((*dest)->left));
            CopyConstructTree(rht, &((*dest)->right));
        }
    }
    void DestoryTree(Node *source)
    {
        if (source)
        {
            Node *lft = source->left;
            Node *rht = source->right;
            delete source;
            DestoryTree(lft);
            DestoryTree(rht);
        }
    }
    friend void swap(BinaryTree &lft, BinaryTree &rht)
    {
        using std::swap;
        swap(lft.root, rht.root);
    }
private:
    Node *root;
};
}
#endif

