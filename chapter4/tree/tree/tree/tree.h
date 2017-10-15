#pragma once
#ifndef TREE_H_
#define TREE_H_

namespace zy {
template<typename Object>
class Tree
{
public:
    typedef typename Object ValueType;
protected:
    class Node
    {
    public:
        Node(const ValueType &item = ValueType{}, Node *child = nullptr, Node *sibling = nullptr)
            :data(item), firstChild(child), nextSibling(sibling)
        {}
        Node(const Node &oth)
            :data(oth.data), firstChild(oth.firstChild), nextSibling(oth.nextSibling)
        {}
        Node(Node &&oth)
            :data(std::move(oth.data)), firstChild(std::move(oth.firstChild)), nextSibling(std::move(oth.nextSibling))
        {
            oth.nextSibling = nullptr;
            oth.firstChild = nullptr;
        }
    public:
        ValueType data;
        Node *firstChild;
        Node *nextSibling;
    };
private:
};
}

#endif
