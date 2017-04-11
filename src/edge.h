#pragma once

#include <stdint.h>

#include "glm/vec4.hpp"

#include "vertex.h"
#include "gradients.h"

namespace kiwi {
	
	class Edge
	{
	public:
		Edge(const Gradients &gradients, const Vertex &min_y, const Vertex &max_y, std::size_t min_y_index);

		void step();
		float x() const;
		int32_t y_start() const;
		int32_t y_end() const;
		const glm::vec4 &color() const;

	private:
		float x_;
		float x_step_;
		int32_t y_start_;
		int32_t y_end_;
		glm::vec4 color_;
		glm::vec4 color_step_;
	};

}