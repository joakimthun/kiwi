#include "edge.h"

#include <math.h>

namespace kiwi {

	Edge::Edge(const Gradients &gradients, const Vertex &min_y, const Vertex &max_y, std::size_t min_y_index)
	{
		y_start_ = static_cast<int32_t>(ceil(min_y.y()));
		y_end_ = static_cast<int32_t>(ceil(max_y.y()));

		const auto y_dist = max_y.y() - min_y.y();
		const auto x_dist = max_y.x() - min_y.x();
		const float y_prestep = y_start_ - min_y.y();

		x_step_ = x_dist / y_dist;
		x_ = min_y.x() + y_prestep * x_step_;

		float x_prestep = x_ - min_y.x();

		const auto color_y_step = gradients.color_y_step();
		const auto color_x_step = gradients.color_x_step();

		color_ = gradients.get_color(min_y_index) + ((color_y_step * y_prestep) + (color_x_step * x_prestep));
		color_step_ = color_y_step + (color_x_step * x_step_);
	}

	void Edge::step()
	{
		x_ += x_step_;
		color_ += color_step_;
	}

	float Edge::x() const
	{
		return x_;
	}

	int32_t Edge::y_start() const
	{
		return y_start_;
	}

	int32_t Edge::y_end() const
	{
		return y_end_;
	}

	const glm::vec4 &Edge::color() const
	{
		return color_;
	}

}
