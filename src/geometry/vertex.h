#pragma once

#include "../math/vec4.h"
#include "../math/mat4.h"

namespace kiwi {

	class Vertex
	{
	public:
		Vertex(const Vec4 &position, const Vec4 &text_coords);
		Vertex(float x, float y, float z, float w, float r, float g, float b, float a);

		float x() const;
		float y() const;
		float z() const;
		float w() const;
		const Vec4 &Vertex::text_coords() const;
		Vertex transform(const Mat4 &transform) const;
		Vertex perspective_divide() const;
		Vertex screen_space_transform(float half_width, float half_height) const;

	private:
		Vertex(float x, float y, float z, float w, const Vec4 &text_coords);

		Vec4 position_;
		Vec4 text_coords_;
	};

}