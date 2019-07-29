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
	void add_adjance(std::shared_ptr<Vertex> other, int weight = 1)
	{
		adjance_vertexes_.push_back(other);
		other->increase_indegree();
        weights_.push_back(weight);
	}
	void add_adjance(std::weak_ptr<Vertex> other, int weight = 1)
	{
		adjance_vertexes_.push_back(other);
		other.lock()->increase_indegree();
        weights_.push_back(weight);
	}
	const T& value() const noexcept
	{
		return v_;
	}
	std::list<std::weak_ptr<Vertex>>& adjance() noexcept
	{
		return adjance_vertexes_;
	}
    std::vector<int>& weights() noexcept
    {
        return weights_;
    }
    int weight(std::weak_ptr<Vertex> adj) const noexcept
    {
        auto ite = std::find(adjance_vertexes_.begin(), adjance_vertexes_.end(), adj);
        if (ite == adjance_vertexes_.end())
        {
            throw std::exception("not a adjance");
        }
        return weights_[ite - adjance_vertexes_.begin()];
    }
	void set_distance(int dist) noexcept
	{
		distance_ = dist;
	}
	void set_prepath(std::weak_ptr<Vertex> pre)
	{
		path_ = pre;
	}
    void set_known(bool know) noexcept
    {
        known_ = know;
    }
    bool known() const noexcept
    {
        return known_;
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
    std::vector<int> weights_;
	int topological_sort_number_;
	int indegree_;
    bool known_;
	int distance_;
	std::weak_ptr<Vertex> path_;
};

#endif