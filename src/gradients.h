#pragma once

#include <array>
#include "glm/vec4.hpp"

#include "vertex.h"

namespace kiwi {

	class Gradients
	{
	public:
		Gradients(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y);

		const glm::vec4 &get_color(std::size_t index) const;
		const glm::vec4 &color_x_step() const;
		const glm::vec4 &color_y_step() const;

	private:
		std::array<glm::vec4, 3> colors_;
		glm::vec4 color_x_step_;
		glm::vec4 color_y_step_;
	};

}