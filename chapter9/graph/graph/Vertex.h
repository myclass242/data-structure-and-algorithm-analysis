#ifndef VERTEX_H_
#define VERTEX_H_

#include <list>
#include <memory>

template <typename T>
class Vertex : public std::enable_shared_from_this<Vertex<T>>
{
public:
    struct VertexInfo
    {
        std::weak_ptr<Vertex> vertex_;
        int weight_;
    };
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
        VertexInfo info{ other, weight };
        adjance_vertexes_.push_back(info);
		other->increase_indegree();

        VertexInfo pre_info{ this->weak_from_this(), weight };
        other->pre_adjance_vertexes_.push_back(pre_info);
	}
	void add_adjance(std::weak_ptr<Vertex> other, int weight = 1)
	{
        VertexInfo info{ other, weight };
		adjance_vertexes_.push_back(info);
		other.lock()->increase_indegree();

        VertexInfo pre_info{ this->weak_from_this(), weight };
        other.lock()->pre_adjance_vertexes_.push_back(pre_info);
	}
	const T& value() const noexcept
	{
		return v_;
	}
    std::list<VertexInfo>& adjance() noexcept
	{
		return adjance_vertexes_;
	}
    std::list<VertexInfo>& pre_adjance() noexcept
    {
        return pre_adjance_vertexes_;
    }
    int weight(std::weak_ptr<Vertex> adj) const noexcept
    {
        return get_weight(adjance_vertexes_, adj);
    }
    int pre_weight(std::weak_ptr<Vertex> adj) const noexcept
    {
        return get_weight(pre_adjance_vertexes_, adj);
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
    int get_weight(const std::list<VertexInfo>& vertexes, std::weak_ptr<Vertex> adj) const noexcept
    {
        auto ite = std::find_if(vertexes.begin(), vertexes.end(),
            [&](const VertexInfo& info) { return adj == info.vertex_; });
        if (ite == vertexes.end())
        {
            throw std::exception("not a adjance");
        }
        return ite->weight_;
    }
private:
	T v_;
	std::list<VertexInfo> adjance_vertexes_;
    std::list<VertexInfo> pre_adjance_vertexes_;
	int topological_sort_number_;
	int indegree_;
    bool known_;
	int distance_;
	std::weak_ptr<Vertex> path_;
};

#endif