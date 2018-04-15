#pragma once
#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <stdlib.h>
#include <iostream>
#include <utility>

namespace zy {
template<typename Comparable>
class BinarySearchTree
{
protected:
    class Node
    {
    public:
        Node(const Comparable &item, Node *lft = nullptr, Node *rht = nullptr)
            :data(item), left(lft), right(rht)
        {}

        Node(Comparable &&item, Node *lft = nullptr, Node *rht = nullptr)
            :data(std::move(item)), left(lft), right(rht)
        {}
    public:
        Comparable data;
        Node *left;
        Node *right;
    };
public:
    BinarySearchTree()
        :root(nullptr)
    {
    }
    BinarySearchTree(const BinarySearchTree &oth)
        :BinarySearchTree()
    {
        root = clone(oth.root);
    }
    BinarySearchTree(BinarySearchTree &&oth) noexcept
        :root(std::move(oth.root))
    {
        oth.root = nullptr;
    }
    ~BinarySearchTree()
    {
        destoryBinaryTree(root);
    }
    BinarySearchTree &operator=(BinarySearchTree oth)
    {
        swap(*this, oth);
        return *this;
    }
    void insert(const Comparable &data)
    {
        Comparable rvalueData = data;
        do_insert(&root, std::move(rvalueData));
    }
    void insert(Comparable &&data)
    {
        do_insert(&root, std::move(data));
    }
    bool empty(void) const
    {
        return nullptr == root;
    }
    void remove(const Comparable &data)
    {
        /*if (empty())
        {
            return;
        }
        if (data == root->data)
        {
            free(root);
            root = nullptr;
        }
        Node *parentNode = findParent(root, data);
        if (!parentNode)
        {
            return;
        }
        if (parentNode->left && data == parentNode->left->data)
        {
            Node *temp = parentNode->left;
            parentNode->left = mergeSameParentTrees(parentNode->left);
            free(temp);
        }
        else if (parentNode->right && data == parentNode->right->data)
        {
            Node *temp = parentNode->right;
            parentNode->right = mergeSameParentTrees(parentNode->right);
            free(temp);
        }*/
        remove(data, &root);
    }
    const Comparable &findMin(void) const
    {
        if (empty())
        {
            std::cout << "Binary search tree is empty" << std::endl;
            exit(EXIT_FAILURE);
        }
        Node *min = findMinNode(root);
        return min->data;
    }
    const Comparable &findMax(void) const
    {
        if (empty())
        {
            std::cout << "Binary search tree is empty" << std::endl;
            exit(EXIT_FAILURE);
        }
        Node *max = findMaxNode(root);
        return max->data;
    }
    bool contain(const Comparable &data) const
    {
        //if (empty())
        //{
        //    return false;
        //}
        //if (data == root->data)
        //{
        //    return true;
        //}
        //return findParent(root, data);  //如果可以找到匹配data的父节点则证明tree包含data
        return contain(data, root);
    }
    void makeEmpty(void)
    {
        destoryBinaryTree(root);
        root = nullptr;
    }
    void printTree(std::ostream &out) const
    {
        inorderTraversal(root, out);
    }
private:
    friend void swap(BinarySearchTree &lft, BinarySearchTree &oth)
    {
        using std::swap;
        swap(lft.root, oth.root);
    }
    void remove(const Comparable &data, Node **t)
    {
        if (!(*t))
        {
            return;
        }
        if (data < (*t)->data)
        {
            remove(data, &((*t)->left));
        }
        else if (data > (*t)->data)
        {
            remove(data, &((*t)->right));
        }
        else if ((*t)->left && (*t)->right)
        {
            (*t)->data = findMinNode((*t)->right)->data;
            remove((*t)->data, &((*t)->right));
        }
        else
        {
            Node *oldNode = *t;
            *t = (*t)->left ? (*t)->left : (*t)->right;
            free(oldNode);
        }
    }
    bool contain(const Comparable &data, Node *nd) const
    {
        if (!nd)
        {
            return false;
        }
        if (data < nd->data)
        {
            return contain(data, nd->left);
        }
        else if (data > nd->data)
        {
            return contain(data, nd->right);
        }
        else
        {
            return true;
        }
    }
    void inorderTraversal(const Node *nd, std::ostream &out) const
    {
        if (!nd)
        {
            return;
        }
        inorderTraversal(nd->left, out);
        out << nd->data << ' ';
        inorderTraversal(nd->right, out);
    }
    void pastorderTraversal(const Node *nd, std::ostream &out) const
    {
        if (!nd)
        {
            return;
        }
        pastorderTraversal(nd->left, out);
        pastorderTraversal(nd->right, out);
        out << nd->data << ' ';
    }
    void preorderTraversal(const Node *nd, std::ostream &out) const
    {
        if (!nd)
        {
            return;
        }
        out << nd->data << ' ';
        preorderTraversal(nd->left, out);
        preorderTraversal(nd->right, out);
    }
    Node *mergeSameParentTrees(Node *parent)
    {
        if (!parent)
        {
            return nullptr;
        }
        if (!(parent->left))
        {
            return parent->right;
        }
        else if (!(parent->right))
        {
            return parent->left;
        }
        else
        {
            Node *min = findMinNode(parent->right);
            min->left = parent->left;
            return parent->right;
        }
    }
    /*Node *findParent(Node *nd, const Comparable &data) const
    {
        if (!nd)
        {
            return nullptr;
        }

        if (nd->data < data)
        {
            if (!(nd->right))
            {
                return nullptr;
            }
            else if (data == nd->right->data)
            {
                return nd;
            }
            else
            {
                return findParent(nd->right, data);
            }
        }
        else if (nd->data > data)
        {
            if (!(nd->left))
            {
                return nullptr;
            }
            else if (data == nd->left->data)
            {
                return nd;
            }
            else
            {
                return findParent(nd->left, data);
            }
        }
        else
        {
            std::cout << "查找匹配值的父节点异常" << std::endl;
            return nullptr;
        }
    }*/
    Node *findMinNode(const Node *nd) const
    {
        if (!nd)
        {
            return nullptr;
        }
        if (!(nd->left))
        {
            return const_cast<Node *>(nd);
        }
        return findMinNode(nd->left);
    }
    Node *findMaxNode(const Node *nd) const
    {
        if (nd)
        {
            while (nd->right)
            {
                nd = nd->right;
            }
        }
        return const_cast<Node *>(nd);
    }
    void do_insert(Node **nd, Comparable &&data)
    {
        if (!(*nd))
        {
            *nd = new Node(std::move(data), nullptr, nullptr);
        }
        else if ((*nd)->data < data)
        {
            do_insert(&((*nd)->right), std::move(data));
        }
        else if((*nd)->data > data)
        {
            do_insert(&((*nd)->left), std::move(data));
        }
        else
        {
            return; //duplicates are ignored
        }
    }
    void destoryBinaryTree(Node *nd)
    {
        if (!nd)
        {
            return;
        }
        destoryBinaryTree(nd->left);
        destoryBinaryTree(nd->right);
        free(nd);
    }
    Node *clone(Node *source)
    {
        if (!source)
        {
            return nullptr;
        }
        else
        {
            return new Node(source->data, clone(source->left), clone(source->right));
        }
    }
private:
    Node *root;
};
}

#endif
