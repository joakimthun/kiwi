#include "vertex.h"

#include <cmath>

#include "../util.h"

namespace kiwi {

	Vertex::Vertex(const Vec4 &position, const Vec4 &text_coords)
		:
		position_(position),
		text_coords_(text_coords)
	{
	}

	Vertex::Vertex()
		:
		position_(Vec4(0, 0, 0, 0)),
		text_coords_(0, 0, 0, 0)
	{
	}	

	Vertex::Vertex(float x, float y, float z, float w, float r, float g, float b, float a)
		:
		position_(Vec4(x, y, z, w)),
		text_coords_(r, g, b, a)
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

	const Vec4 & Vertex::text_coords() const
	{
		return text_coords_;
	}

	Vertex Vertex::transform(const Mat4 &transform) const
	{
		return Vertex(transform * position_, text_coords_);
	}

	Vertex Vertex::lerp(const Vertex &other, float amount) const
	{
		return Vertex(position_.lerp(other.position_, amount), text_coords_.lerp(other.text_coords_, amount));
	}

	Vertex Vertex::perspective_divide() const
	{
		return Vertex(
			position_.x / position_.w,
			position_.y / position_.w,
			position_.z / position_.w,
			position_.w,
			text_coords_);
	}

	Vertex Vertex::screen_space_transform(float half_width, float half_height) const
	{
		return Vertex(
			half_width * x() + (half_width - 0.5f) * w(),
			-half_height * y() + (half_height -0.5f) * w(),
			z(), 
			w(),
			text_coords_);
	}

	bool Vertex::inside_view_frustum() const
	{
		return std::abs(position_.x) <= std::abs(position_.w) && 
			std::abs(position_.y) <= std::abs(position_.w) &&
			std::abs(position_.z) <= std::abs(position_.w);
	}

	Vertex::Vertex(float x, float y, float z, float w, const Vec4 &text_coords)
		:
		position_(Vec4(x, y, z, w)),
		text_coords_(text_coords)
	{
	}

}