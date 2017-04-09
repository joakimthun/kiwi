#pragma once

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

namespace kiwi {

	class Vertex
	{
	public:
		Vertex(float x, float y, float z);
		Vertex(float x, float y, float z, float w);
		Vertex(const glm::vec4 &position);

		float x() const;
		float y() const;
		float z() const;
		float w() const;
		Vertex transform(const glm::mat4 &transform) const;
		Vertex perspective_divide() const;
		Vertex screen_space_transform(float half_width, float half_height) const;

	private:
		glm::vec4 position_;
	};

}