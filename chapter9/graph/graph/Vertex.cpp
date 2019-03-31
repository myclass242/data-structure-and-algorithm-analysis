#include "Vertex.h"

template<typename T>
Vertex<T>::Vertex(IdentType ident)
    : identify(std::move(ident)), topologicalNum(-1), indegree(0)
{
}

template<typename T>
Vertex<T>::~Vertex()
{
}

template<typename T>
void Vertex<T>::addAdjacency(std::shared_ptr<Vertex> adjancency)
{
    adjacencyList.push_back(adjancency);
    adjancency->incIndgree();
}

template<typename T>
void Vertex<T>::incIndegree()
{
    ++indegree;
}

template<typename T>
void Vertex<T>::decIndegree()
{
    --indegree;
}

template<typename T>
int Vertex<T>::getTopnum()
{
    return topologicalNum;
}

template<typename T>
void Vertex<T>::setTopnum(int topnum)
{
    topologicalNum = topnum;
}

template<typename T>
int Vertex<T>::getIndegree()
{
    return indegree;
}

