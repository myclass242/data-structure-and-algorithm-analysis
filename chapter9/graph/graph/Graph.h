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
      for (const auto& vertexInfo : v->adjance()) {
        auto strong = vertexInfo.vertex_.lock();
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
            auto strong = ad.vertex_.lock();
            if (strong->distance() == -1) {
                strong->set_distance(v->distance() + 1);
                strong->set_prepath(v);
                q.push_back(strong);
            }
        }
    }

    for (const auto& ver : vertes_) {
        std::cout << ver->name() << " : " << ver->distance() << " prepath ";
        if (ver->prepath().lock()) {
            std::cout << ver->prepath().lock()->name();
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
  }

  // my weight shortest path
  // Not as goog as dijkstra
  void weight_shortest_path(const T& s)
  {
      auto ver = find_vertex(s);
      if (!ver) {
          return;
      }
      for (auto& vertex : vertes_) {
          vertex->set_distance(INT_MAX);
          ver->set_in_queue(false);
      }
      ver->set_distance(0);
      std::queue<decltype(ver)> q;
      q.push(ver);
      ver->set_in_queue(true);
      while (!q.empty()) {
          auto v = q.front();
          q.pop();
          v->set_in_queue(false);
          for (auto& ad_ver : v->adjance()) {
              auto strong = ad_ver.vertex_.lock();
              if (strong->distance() > v->distance() + ad_ver.weight_) {
                  strong->set_distance(v->distance() + ad_ver.weight_);
                  // If vertex changed, its adjance may need changed too,
                  // so we enqueue the vertex
                  if (!strong->in_queue()) {
                      q.push(strong);
                      strong->set_in_queue(true);
                  }
                  strong->set_prepath(v);
              }
          }
      }

      for (const auto& ver : vertes_) {
          std::cout << ver->name() << " : " << ver->distance() << " prepath ";
          if (ver->prepath().lock()) {
              std::cout << ver->prepath().lock()->name();
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
          auto adj_ite = min->adjance().begin();
          for (; adj_ite != min->adjance().end(); ++adj_ite)
          {
              auto strong = adj_ite->vertex_.lock();
              if (!strong->known())
              {
                  if (strong->distance() > min->distance() + adj_ite->weight_)
                  {
                      // 特殊处理 decreaseKey
                      strong->set_distance(min->distance() + adj_ite->weight_);
                      unknow_distance.decreaseKey(unknow_distance.find(strong));
                      strong->set_prepath(min);
                  }
              }
          }
      }

      //while (!q.empty()) {
      //  std::cout << q.front()->name() << " : " << q.front()->distance() << std::endl;
      //  q.pop();
      //}
      for (const auto& ver : vertes_) {
          std::cout << ver->name() << " : " << ver->distance() << " prepath ";
          if (ver->prepath().lock()) {
              std::cout << ver->prepath().lock()->name();
          }
          std::cout << '\n';
      }
      std::cout << std::endl;
  }
  void weightedNegative(const T& s)
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
      q.push(ver);
      while (!q.empty()) {
          auto v = q.front();
          q.pop();
          v->set_known(false);

          auto adj_ite = v->adjance().begin();
          for (; adj_ite != v->adjance().end(); ++adj_ite)
          {
              auto strong = adj_ite->vertex_.lock();
                if (strong->distance() > v->distance() + adj_ite->weight_)
                {
                    // 特殊处理 decreaseKey
                    strong->set_distance(v->distance() + adj_ite->weight_);
                    strong->set_prepath(v);
                    if (!strong->known()) {
                        q.push(strong);
                        strong->set_known(true);
                    }
                }
          }
      }
  }
  void eventNodeGraph()
  {
      for (auto& vertex : vertes_) {
          vertex->set_distance(0);
          vertex->set_known(false);
      }
      topological_sort();
      struct LessHelper {
          bool operator()(const std::shared_ptr<VertexType>& lhs, const std::shared_ptr<VertexType>& rhs) {
              return lhs->toplogical_sort() < rhs->toplogical_sort();
          }
      };
      BinaryHeap<std::shared_ptr<VertexType>, LessHelper> unknow_distance{ vertes_ };
      while (!unknow_distance.isEmpty()) {
          std::shared_ptr<VertexType> min;
          unknow_distance.deleteMin(min);
          for (auto& adj : min->adjance()) {
              auto strong = adj.vertex_.lock();
              auto dist = std::max(strong->distance(), min->distance() + adj.weight_);
              strong->set_distance(dist);
          }
      }
      for (auto vertex : vertes_) {
          std::cout << vertex->name() << " " << vertex->distance() << " " << vertex->toplogical_sort() << std::endl;
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