#include "vertices3.h"

namespace kiwi {

	Vertices3::Vertices3()
		:
		current_index_(0),
		size(3)
	{
	}

	void Vertices3::push_back(const Vertex &vertex)
	{
		vertices_[current_index_++] = vertex;
	}

	void Vertices3::clear()
	{
		current_index_ = 0;
	}

	bool Vertices3::empty() const
	{
		return current_index_ == 0;
	}

	const Vertex &Vertices3::back() const
	{
		return vertices_[2];
	}

	const Vertex &Vertices3::operator[](std::size_t index) const
	{
		return vertices_[index];
	}

}
