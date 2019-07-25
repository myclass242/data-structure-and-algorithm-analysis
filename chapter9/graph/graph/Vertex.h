#ifndef VERTEX_H_
#define VERTEX_H_

#include <list>
#include <memory>

template <typename T>
class Vertex
{
public:
	Vertex(T v)
		: v_(v),
		topological_sort_number_(-1),
		indegree_(0), 
        distance_(-1)
        //path_(nullptr)
	{}

    const T& name() const noexcept
    {
        return v_;
    }

	void increase_indegree() noexcept
	{
		++indegree_;
	}
	void decrease_indegree() noexcept
	{
		--indegree_;
	}
	int indegree() const noexcept
	{
		return indegree_;
	}
	void set_tological_sort(int number) noexcept
	{
		topological_sort_number_ = number;
	}
	int toplogical_sort() const noexcept
	{
		return topological_sort_number_;
	}
	void add_adjance(std::shared_ptr<Vertex> other)
	{
		adjance_vertexes_.push_back(other);
		other->increase_indegree();
	}
	void add_adjance(std::weak_ptr<Vertex> other)
	{
		adjance_vertexes_.push_back(other);
		other.lock()->increase_indegree();
	}
	const T& value() const noexcept
	{
		return v_;
	}
	std::list<std::weak_ptr<Vertex>> adjance()
	{
		return adjance_vertexes_;
	}
	void set_distance(int dist) noexcept
	{
		distance_ = dist;
	}
	void set_prepath(std::weak_ptr<Vertex> pre)
	{
		path_ = pre;
	}
    int distance() const noexcept
    {
        return distance_;
    }
    std::weak_ptr<Vertex> path() noexcept
    {
        return path_;
    }
private:
	T v_;
	std::list<std::weak_ptr<Vertex>> adjance_vertexes_;
	int topological_sort_number_;
	int indegree_;
	int distance_;
	std::weak_ptr<Vertex> path_;
};

#endif