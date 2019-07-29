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
#include <assert.h>

#include "Vertex.h"
#include "HeapBinary.h"

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

  void add_edge(const T& from, const T& to, bool orient, int weight = 1) 
  {
    auto from_ver = find_vertex(from);
    auto to_ver = find_vertex(to);
    if (!from_ver || !to_ver) {
      std::cout << "not exist" << std::endl;
    }

    do_add_edge(from_ver, to_ver, orient, weight);
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

  void dijkstra(const T& s)
  {
      std::queue<std::shared_ptr<VertexType>> q;
      auto ver = find_vertex(s);
      if (!ver) {
          return;
      }
      for (auto& vertex : vertes_)
      {
          vertex->set_distance(INT_MAX);
          vertex->set_known(false);
      }
      ver->set_distance(0);
      struct LessHelper {
          bool operator()(const std::shared_ptr<VertexType>& lhs, const std::shared_ptr<VertexType>& rhs) {
              return lhs->distance() < rhs->distance();
          }
      };
      BinaryHeap<std::shared_ptr<VertexType>, LessHelper> unknow_distance{ vertes_ };
      while (!unknow_distance.isEmpty())
      {
          std::shared_ptr <VertexType> min;
          unknow_distance.deleteMin(min);
          min->set_known(true);
          q.push(min);
          assert(min->adjance().size() == min->weights().size());
          auto adj_ite = min->adjance().begin();
          auto weights_ite = min->weights().begin();
          for (;
              (adj_ite != min->adjance().end()) && (weights_ite != min->weights().end());
              ++adj_ite, ++weights_ite)
          {
              auto strong = adj_ite->lock();
              if (!strong->known())
              {
                  if (strong->distance() > min->distance() + *weights_ite)
                  {
                      // ÌØÊâ´¦Àí decreaseKey
                      strong->set_distance(min->distance() + *weights_ite);
                      unknow_distance.decreaseKey(unknow_distance.find(strong));
                      strong->set_prepath(min);
                  }
              }
          }
      }

      while (!q.empty()) {
        std::cout << q.front()->name() << " : " << q.front()->distance() << std::endl;
        q.pop();
      }  
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
                   std::shared_ptr<VertexType> to, bool orient, int weight) {
    from->add_adjance(to, weight);
    if (orient) {
      return;
    }
    do_add_edge(to, from, !orient, weight);
  }

 private:
  std::vector<std::shared_ptr<VertexType>> vertes_;
};

#endif