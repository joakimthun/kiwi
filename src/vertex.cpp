#include "vertex.h"

namespace kiwi {

	Vertex::Vertex(const glm::vec4& position, const glm::vec4 &color)
		:
		position_(position),
		color_(color)
	{
	}

	Vertex::Vertex(float x, float y, float z, float w, float r, float g, float b, float a)
		:
		position_(glm::vec4(x, y, z, w)),
		color_(r, g, b, a)
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

	const glm::vec4 &Vertex::color() const
	{
		return color_;
	}

	Vertex Vertex::transform(const glm::mat4 &transform) const
	{
		return Vertex(transform * position_, color_);
	}

	Vertex Vertex::perspective_divide() const
	{
		return Vertex(
			position_.x / position_.w,
			position_.y / position_.w,
			position_.z / position_.w,
			position_.w,
			color_);
	}

	Vertex Vertex::screen_space_transform(float half_width, float half_height) const
	{
		return Vertex(
			half_width * x() + half_width * w(),
			-half_height * y() + half_height * w(),
			z(), 
			w(),
			color_);
	}

	Vertex::Vertex(float x, float y, float z, float w, const glm::vec4 &color)
		:
		position_(glm::vec4(x, y, z, w)),
		color_(color)
	{
	}

}