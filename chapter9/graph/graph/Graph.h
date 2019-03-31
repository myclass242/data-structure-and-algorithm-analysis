#pragma once
#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.h"
#include <vector>
#include <initializer_list>

template <typename T>
class Graph
{
    using IdentType = T;
    using VertexPtr = std::shared_ptr<Vertex<IdentType>>;
public:
    explicit Graph(int vertexNum);
    ~Graph();

    VertexPtr getVertex(IdentType vertexName);

    void addVertex(IdentType vertexName);
    void addVertex(std::initializer_list<IdentType> list);

    void addEdge(IdentType from, IdentType to, bool orient = true);

    void topologicalSort(void);

private:
    void doAddEdge(VertexPtr from, VertexPtr to, bool orient);
private:
    std::vector<VertexPtr> vertexs;
};

#endif