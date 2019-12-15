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

void test_dijkstra()
{
    Graph<int> graph;
    graph.add_vertex({ 1, 2, 3, 4, 5, 6, 7 });
    graph.add_edge(1, 2, true, 2);
    //graph.add_edge(1, 3, true,);
    graph.add_edge(1, 4, true, 1);
    graph.add_edge(2, 4, true, 3);
    graph.add_edge(2, 5, true, 10);
    graph.add_edge(3, 1, true, 4);
    graph.add_edge(3, 6, true, 5);
    graph.add_edge(4, 3, true, 2);
    graph.add_edge(4, 5, true, 2);
    graph.add_edge(4, 6, true, 8);
    graph.add_edge(4, 7, true, 4);
    //graph.add_edge(5, 4, true);
    graph.add_edge(5, 7, true, 6);
    graph.add_edge(7, 6, true, 1);

    graph.dijkstra(1);
    graph.weight_shortest_path(1);
}

void test_event_node_graph()
{
    Graph<int> graph;
    graph.add_vertex({ 1, 2, 3, 4, 5, 6, 66, 77, 88, 7, 8, 9, 1010, 10 });
    graph.add_edge(1, 2, true, 3);
    graph.add_edge(1, 3, true, 2);
    graph.add_edge(2, 66, true, 0);
    graph.add_edge(3, 66, true, 0);
    graph.add_edge(2, 4, true, 3);
    graph.add_edge(3, 5, true, 1);
    graph.add_edge(66, 6, true, 2);
    graph.add_edge(6, 77, true, 0);
    graph.add_edge(6, 88, true, 0);
    graph.add_edge(4, 77, true, 0);
    graph.add_edge(5, 88, true, 0);
    graph.add_edge(77, 7, true, 3);
    graph.add_edge(5, 9, true, 4);
    graph.add_edge(88, 8, true, 2);
    graph.add_edge(7, 1010, true, 0);
    graph.add_edge(8, 1010, true, 0);
    graph.add_edge(9, 1010, true, 0);
    graph.add_edge(1010, 10, true, 1);

    graph.eventNodeGraph();

}
