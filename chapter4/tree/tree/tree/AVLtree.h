#pragma once
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <utility>
#include <ostream>
#include <cmath>

namespace zy {
template<typename T>
class AVLtree
{
public:
    typedef typename T ValueType;
    typedef int HightType;
protected:
    class Node
    {
    public:
        Node(const ValueType &v = ValueType{}, Node *lt = nullptr, Node *rt = nullptr, HightType h = 0)
            :data(v), left(lt), right(rt), hight(h)
        {}
        Node(ValueType &&v, Node *lt = nullptr, Node *rt = nullptr, HightType h = 0)
            :data(std::move(v)), left(lt), right(rt), hight(h)
        {}
        Node(const Node &) = delete;
        Node(Node &&) = delete;
    public:
        ValueType data;
        Node *left;
        Node *right;
        HightType hight;
    };
public:
    AVLtree()
        :root(nullptr), theSize(0)
    {}
    AVLtree(const AVLtree &oth)
    {
        root = clone(oth->root);
        theSize = oth.theSize;
    }
    AVLtree(AVLtree &&oth)
        :root(std::move(oth.root)), theSize(std::move(oth.theSize))
    {
        oth.root = nullptr;
    }
    ~AVLtree()
    {
        clear(root);
    }
    AVLtree &operator=(AVLtree oth)
    {
        swap(*this, oth);
        return *this;
    }
    void preorderPrint(std::ostream &out) const
    {
        preorderPrint(root, out);
    }
    void inorderPrint(std::ostream &out) const
    {
        inorderPrint(root, out);
    }
    void postorderPrint(std::ostream &out) const
    {
        postorderPrint(root, out);
    }
    bool empty(void) const
    {
        return nullptr == root;
    }
    size_t size(void) const
    {
        return theSize;
    }
    HightType hight(void) const
    {
        return hight(root);
    }
    void insert(const ValueType &v)
    {
        insert(root, v);
        ++theSize;
    }
    void remove(const ValueType &v)
    {
        bool removeFlag = false;
        remove(root, v, removeFlag);
        if (true == removeFlag)
        {
            --theSize;
        }
    }
private:
    friend void swap(AVLtree &lft, AVLtree &rht)
    {
        using std::swap;
        swap(lft.root, rht.root);
        swap(lft.theSize, rht.theSize);
    }
    HightType max(const HightType &a, const HightType &b) const
    {
        return a < b ? b : a;
    }
    //插入左子树的左节点，右旋恢复平衡
    Node *rightRotation(Node * &nd)
    {
        Node * lchild = nd->left;
        nd->left = lchild->right;
        lchild->right = nd;
        nd->hight = max(hight(nd->left), hight(nd->right)) + 1;
        lchild->hight = max(hight(lchild->left), hight(lchild->right)) + 1;
        return lchild;
    }
    //插入右子树的右节点，左旋恢复平衡
    Node *leftRotation(Node * &nd)
    {
        Node * rchild = nd->right;
        nd->right = rchild->left;
        rchild->left = nd;
        nd->hight = max(hight(nd->left), hight(nd->right)) + 1;
        rchild->hight = max(hight(rchild->left), hight(rchild->right)) + 1;
        return rchild;
    }
    //插入左子树的右节点,先左子树左旋，再右旋
    Node *leftRightRotation(Node * &nd)
    {
        nd->left = leftRotation(nd->left);
        return rightRotation(nd);
    }
    //插入右子树的左节点，先右子树右旋，在左旋
    Node *rightLeftRotation(Node * &nd)
    {
        nd->right = rightRotation(nd->right);
        return leftRotation(nd);
    }
    HightType hight(const Node *nd) const
    {
        if (nullptr == nd)
        {
            return 0;
        }
        return nd->hight;
    }
    void balance(Node * &nd)
    {
        if (nullptr == nd)
        {
            return;
        }

        if (hight(nd->left) - hight(nd->right) > 1) 
        {
            if (hight(nd->left->left) >= hight(nd->left->right)) //插入左孩子的左子树,右旋
            {
                nd = rightRotation(nd);
            }
            else                                                //插入左孩子的右子树，先左旋后右旋
            {
                nd = leftRightRotation(nd);
            }
        }
        else if (hight(nd->right) - hight(nd->left) > 1)
        {
            if (hight(nd->right->right) >= hight(nd->right->left))    //插入右孩子的右子树，左旋
            {
                nd = leftRotation(nd);
            }
            else                                               //插入右孩子的左子树，先右旋再左旋
            {
                nd = rightLeftRotation(nd);
            }
        }

        nd->hight = max(hight(nd->left), hight(nd->right)) + 1;
    }
    void insert(Node * &nd, const ValueType &v)
    {
        if (!nd)
        {
            nd = new Node(v, nullptr, nullptr, 0);
        }
        else if(v < nd->data)
        {
            insert(nd->left, v);
        }
        else if(nd->data < v)
        {
            insert(nd->right, v);
        }
        
        balance(nd);
    }
    Node *findMinNode(const Node *nd) const
    {
        while (nullptr != nd->left)
        {
            nd = nd->left;
        }
        return nd;
    }
    void remove(Node * &nd, const ValueType &v, bool &removeFlag)
    {
        if (nullptr == nd)
        {
            return;
        }
        else if (v < nd->data)
        {
            remove(nd->left, v, removeFlag);
        }
        else if (v > nd->data)
        {
            remove(nd->right, v, removeFlag);
        }
        else if ((nd->left != nullptr) && (nd->right != nullptr))
        {
            nd->data = findMinNode(nd->right)->data;
            remove(nd->right, nd->data, removeFlag);
        }
        else
        {
            Node *old = nd;
            nd = nd->left ? nd->left : nd->right;
            delete old;
            removeFlag = true;
        }

        balance(nd);
    }
    Node *clone(const Node *src)
    {
        if (!src)
        {
            return nullptr;
        }
        return new Node(src->data, clone(src -> left), clone(src->right), src->hight);
    }
    void clear(Node *nd)
    {
        if (!nd)
        {
            return;
        }
        clear(nd->left);
        clear(nd->right);
        free(nd);
        nd = nullptr;
    }
    void preorderPrint(const Node *nd, std::ostream &out) const
    {
        if (nd)
        {
            preorderPrint(nd->left, out);
            preorderPrint(nd->right, out);
            out << nd->data << ' ';
        }
    }
    void inorderPrint(const Node *nd, std::ostream &out) const
    {
        if (nd)
        {
            inorderPrint(nd->left, out);
            out << nd->data << ' ';
            inorderPrint(nd->right, out);
        }
    }
    void postorderPrint(const Node *nd, std::ostream &out) const
    {
        if (nd)
        {
            out << nd->data << ' ';
            postorderPrint(nd->left, out);
            postorderPrint(nd->right, out);
        }
    }
private:
    Node *root;
    size_t theSize;
};
}
#endif
