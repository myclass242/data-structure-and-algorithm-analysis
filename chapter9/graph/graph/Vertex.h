#pragma once
#ifndef VERTEX_H_
#define VERTEX_H_

#include <list>
#include <memory>


template <typename T>
class Graph;

template <typename T>
class Vertex
{
    using IdentType = T;
    friend class Graph<IdentType>;
public:
    explicit Vertex(IdentType ident);
    ~Vertex();

    IdentType name() { return identify; }
    void addAdjacency(std::shared_ptr<Vertex> adjancency);
    void incIndegree();
    void decIndegree();
    int getTopnum();
    void setTopnum(int topnum);
    int getIndegree();
private:
    IdentType identify;
    std::list<std::shared_ptr<Vertex>> adjacencyList;
    int indegree;
    int topologicalNum;
};

#endif
