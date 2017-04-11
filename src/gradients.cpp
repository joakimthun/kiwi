#include "gradients.h"

namespace kiwi {

	Gradients::Gradients(const Vertex &min_y, const Vertex &mid_y, const Vertex& max_y)
	{
		colors_[0] = min_y.color();
		colors_[1] = mid_y.color();
		colors_[2] = max_y.color();

		const auto one_over_dx = 1.0f /
			(((mid_y.x() - max_y.x()) *
			(min_y.y() - max_y.y())) -
				((min_y.x() - max_y.x()) *
				(mid_y.y() - max_y.y())));

		const float one_over_dy = -one_over_dx;

		color_x_step_ =
			(((colors_[1] - colors_[2]) * (min_y.y() - max_y.y())) - (colors_[0] - colors_[2]) * (mid_y.y() - max_y.y())) * one_over_dx;

		color_y_step_ =
			(((colors_[1] - colors_[2]) * (min_y.x() - max_y.x())) - (colors_[0] - colors_[2]) * (mid_y.x() - max_y.x())) * one_over_dy;
	}

	const glm::vec4 &Gradients::get_color(std::size_t index) const
	{
		return colors_[index];
	}

	const glm::vec4 & Gradients::color_x_step() const
	{
		return color_x_step_;
	}

	const glm::vec4 & Gradients::color_y_step() const
	{
		return color_y_step_;
	}

}
