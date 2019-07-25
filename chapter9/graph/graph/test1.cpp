#include "test1.h"

void test_topological_sort()
{
    Graph<int> graph;
    graph.add_vertex({ 1, 2, 3, 4, 5, 6, 7 });
    graph.add_edge(1, 2, true);
    graph.add_edge(1, 3, true);
    graph.add_edge(1, 4, true);
    graph.add_edge(2, 4, true);
    graph.add_edge(2, 5, true);
    graph.add_edge(3, 6, true);
    graph.add_edge(4, 3, true);
    graph.add_edge(4, 6, true);
    graph.add_edge(4, 7, true);
    graph.add_edge(5, 4, true);
    graph.add_edge(5, 7, true);
    graph.add_edge(7, 6, true);

    graph.topological_sort();
}

void test_unweight_shortest_path()
{
    Graph<int> graph;
    graph.add_vertex({ 1, 2, 3, 4, 5, 6, 7 });
    graph.add_edge(1, 2, true);
    graph.add_edge(1, 3, true);
    graph.add_edge(1, 4, true);
    graph.add_edge(2, 4, true);
    graph.add_edge(2, 5, true);
    graph.add_edge(3, 6, true);
    graph.add_edge(4, 3, true);
    graph.add_edge(4, 6, true);
    graph.add_edge(4, 7, true);
    graph.add_edge(5, 4, true);
    graph.add_edge(5, 7, true);
    graph.add_edge(7, 6, true);

    graph.unweight_shortest_path(1);
}
