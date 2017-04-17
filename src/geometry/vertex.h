#pragma once

#include "../math/vec4.h"
#include "../math/mat4.h"

namespace kiwi {

	class Vertex
	{
	public:
		Vertex(const Vec4 &position, const Vec4 &text_coords, const Vec4 &normal);
		Vertex();
		Vertex(float x, float y, float z, float w, float r, float g, float b, float a);

		float x() const;
		float y() const;
		float z() const;
		float w() const;

		const Vec4 &Vertex::text_coords() const;
		const Vec4 &Vertex::normal() const;
		Vertex transform(const Mat4 &transform, const Mat4 &normal_transform) const;
		Vertex lerp(const Vertex &other, float amount) const;
		Vertex perspective_divide() const;
		Vertex screen_space_transform(float half_width, float half_height) const;
		bool inside_view_frustum() const;

	private:
		Vertex(float x, float y, float z, float w, const Vec4 &text_coords, const Vec4 &normal);

		Vec4 position_;
		Vec4 text_coords_;
		Vec4 normal_;
	};

}