#include "vertex.h"

namespace kiwi {

	Vertex::Vertex(float x, float y, float z)
		:
		position_(glm::vec4(x, y, z, 1))
	{
	}

	Vertex::Vertex(float x, float y, float z, float w)
		:
		position_(glm::vec4(x, y, z, w))
	{
	}

	Vertex::Vertex(const glm::vec4& position)
		:
		position_(position)
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

	float Vertex::z() const
	{
		return position_.z;
	}

	float Vertex::w() const
	{
		return position_.w;
	}

	Vertex Vertex::transform(const glm::mat4 &transform) const
	{
		return Vertex(transform * position_);
	}

	Vertex Vertex::perspective_divide() const
	{
		return Vertex(
			position_.x / position_.w,
			position_.y / position_.w,
			position_.z / position_.w,
			position_.w);
	}

	Vertex Vertex::screen_space_transform(float half_width, float half_height) const
	{
		return Vertex(
			half_width * x() + half_width * w(),
			-half_height * y() + half_height * w(),
			z(), w());
	}

}
