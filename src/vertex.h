#pragma once

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

namespace kiwi {

	class Vertex
	{
	public:
		Vertex(float x, float y);

		float x() const;
		float y() const;
		Vertex& transform(const glm::mat4 &tranform);

	private:
		glm::vec4 position_;
	};

}