#include "vertex.h"

namespace kiwi {

	Vertex::Vertex(float x, float y)
		:
		position_(glm::vec4(x, y, 0, 1))
	{
	}

	float Vertex::x() const
	{
		return position_.x;
	}

	float Vertex::y() const
	{
		return position_.y;
	}

	Vertex& Vertex::transform(const glm::mat4 &tranform)
	{
		position_ = tranform * position_;
		return *this;
	}

}
