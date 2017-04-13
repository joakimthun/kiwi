#pragma once

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

namespace kiwi {

	class Vertex
	{
	public:
		Vertex(const glm::vec4 &position, const glm::vec4 &text_coords);
		Vertex(float x, float y, float z, float w, float r, float g, float b, float a);

		float x() const;
		float y() const;
		float z() const;
		float w() const;
		const glm::vec4 &Vertex::text_coords() const;
		Vertex transform(const glm::mat4 &transform) const;
		Vertex perspective_divide() const;
		Vertex screen_space_transform(float half_width, float half_height) const;

	private:
		Vertex(float x, float y, float z, float w, const glm::vec4 &text_coords);

		glm::vec4 position_;
		glm::vec4 text_coords_;
	};

}