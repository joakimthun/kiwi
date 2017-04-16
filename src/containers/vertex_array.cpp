#include "vertex_array.h"

namespace kiwi {

	VertexArray::VertexArray()
		:
		current_index_(0),
		size(3)
	{
	}

	void VertexArray::push_back(const Vertex &vertex)
	{
		vertices_[current_index_++] = vertex;
	}

	void VertexArray::clear()
	{
		current_index_ = 0;
	}

	bool VertexArray::empty() const
	{
		return current_index_ == 0;
	}

	const Vertex &VertexArray::back() const
	{
		return vertices_[2];
	}

	const Vertex &VertexArray::operator[](std::size_t index) const
	{
		return vertices_[index];
	}

}
