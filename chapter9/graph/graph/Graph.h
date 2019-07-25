#pragma once
#ifndef GRAPH_H_
#define GRAPH_H_

#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <iostream>

#include "Vertex.h"

template <typename T>
class Graph {
  using VertexType = Vertex<T>;

 public:
  Graph() {}

  void add_vertex(const T& v) 
  {
    auto ver = find_vertex(v);
    if (ver) {
      std::cout << "exist" << std::endl;
      return;
    }

    vertes_.push_back(std::make_shared<VertexType>(v));
  }
  void add_vertex(const std::initializer_list<T>& vertex_list) {
    for (const auto& v : vertex_list) {
      add_vertex(v);
    }
  }

  void add_edge(const T& from, const T& to, bool orient) 
  {
    auto from_ver = find_vertex(from);
    auto to_ver = find_vertex(to);
    if (!from_ver || !to_ver) {
      std::cout << "not exist" << std::endl;
    }

    do_add_edge(from_ver, to_ver, orient);
  }
  void topological_sort() {
    std::queue<std::shared_ptr<VertexType>> q;
    for (const auto& vertex : vertes_) {
      if (vertex->indegree() == 0) {
        q.push(vertex);
      }
    }
    int count = 0;
    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      v->set_tological_sort(count++);
      for (const auto& vertex : v->adjance()) {
        auto strong = vertex.lock();
        strong->decrease_indegree();
        if (strong->indegree() == 0) {
          q.push(strong);
        }
      }
    }
    if (!q.empty()) {
      throw std::exception("cycle graph");
    }

    for (const auto& ver : vertes_) {
        std::cout << ver->name() << " : " << ver->toplogical_sort() << '\n';
    }
    std::cout << std::endl;
  }
  void unweight_shortest_path(const T& s) 
  {
    auto ver = find_vertex(s);
    if (!ver) {
      return;
    }

    for (auto& vertex : vertes_) {
      vertex->set_distance(-1);
    }
    ver->set_distance(0);
    std::deque<std::shared_ptr<VertexType>> q;
    q.push_back(ver);
    while (!q.empty()) {
        auto v = q.front();
        q.pop_front();
        for (auto ad : v->adjance()) {
            auto strong = ad.lock();
            if (strong->distance() == -1) {
                strong->set_distance(v->distance() + 1);
                strong->set_prepath(v);
                q.push_back(strong);
            }
        }
    }

    for (const auto& ver : vertes_) {
        std::cout << ver->name() << " : " << ver->distance() << " prepath ";
        if (ver->path().lock()) {
            std::cout << ver->path().lock()->name();
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
  }

 private:
    std::shared_ptr<VertexType> find_vertex(const T& x)
    {
        auto ite = std::find_if(
            vertes_.begin(), vertes_.end(),
            [&](const std::shared_ptr<VertexType>& v) { return v->value() == x; });
        if (ite == vertes_.end()) {
            return nullptr;
        }

        return *ite;
    }
  void do_add_edge(std::shared_ptr<VertexType> from,
                   std::shared_ptr<VertexType> to, bool orient) {
    from->add_adjance(to);
    if (orient) {
      return;
    }
    do_add_edge(to, from, !orient);
  }

 private:
  std::vector<std::shared_ptr<VertexType>> vertes_;
};

#endif