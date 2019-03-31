#include "Graph.h"

#include <exception>
#include <algorithm>
#include <iostream>
#include <queue>


template<typename T>
Graph<T>::Graph(int vertexNum)
    : vertexs(vertexNum)
{
}

template <typename T>
Graph<T>::~Graph()
{
}

template<typename T>
typename Graph<T>::VertexPtr Graph<T>::getVertex(IdentType vertexName)
{
    auto ite = std::find_if(vertexs.begin(), vertexs.end(), [&](const auto& vertex)
    {
        return vertexName == vertex.name();
    });
    if (ite == vertexs.end())
    {
        return nullptr;
    }
    return *ite;
}

template<typename T>
void Graph<T>::addVertex(IdentType vertexName)
{
    if (getVertex(vertexName))
    {
        std::cout << "vertex " << vertexName << " exist" << std::endl;
        return;
    }

    auto vertexPtr = std::make_shared<Vertex>(vertexName);
    vertexs.push_back(vertexPtr);
}

template<typename T>
void Graph<T>::addVertex(std::initializer_list<IdentType> list)
{
    for (auto& vertexName : list)
    {
        addVertex(vertexName);
    }
}

template<typename T>
void Graph<T>::addEdge(IdentType from, IdentType to, bool orient)
{
    auto fromVertex = getVertex(from);
    auto toVertex = getVertex(to);
    if (!fromVertex || !toVertex)
    {
        std::cout << "vertex must exist" << std::endl;
        return;
    }

    doAddEdge(fromVertex, toVertex, orient);
}

template<typename T>
void Graph<T>::topologicalSort(void)
{
    std::queue<VertexPtr> zeroIndegree;
    for (const auto& vertex : vertexs)
    {
        if (vertex->getIndegree() == 0)
        {
            zeroIndegree.push(vertex);
        }
    }

    int counter = 0;
    while (!zeroIndegree.empty())
    {
        auto vert = zeroIndegree.front();
        zeroIndegree.pop();

        vert->setTopnum(++counter);

        for (auto& vertex : vert->adjacencyList)
        {
            vertex->decIndegree();
            if (vertex->getIndegree() == 0)
            {
                zeroIndegree.push(vertex);
            }
        }
    }

    if (counter != vertexs.size())
    {
        throw std::exception("cycle graph");
    }
}

template<typename T>
void Graph<T>::doAddEdge(VertexPtr from, VertexPtr to, bool orient)
{
    from->addAdjacency(to);
    to->incIndegree();
    if (orient)
    {
        return;
    }
    doAddEdge(to, from, !orient);
}
