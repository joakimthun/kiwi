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

		text_coord_x_ = gradients.get_text_coord_x(min_y_index) +
			gradients.text_coord_xx_step() * x_prestep +
			gradients.text_coord_xy_step() * y_prestep;

		text_coord_x_step_ = gradients.text_coord_xy_step() + gradients.text_coord_xx_step() * x_step_;

		text_coord_y_ = gradients.get_text_coord_y(min_y_index) +
			gradients.text_coord_yx_step() * x_prestep +
			gradients.text_coord_yy_step() * y_prestep;

		text_coord_y_step_ = gradients.text_coord_yy_step() + gradients.text_coord_yx_step() * x_step_;
	}

	void Edge::step()
	{
		x_ += x_step_;
		text_coord_x_ += text_coord_x_step_;
		text_coord_y_ += text_coord_y_step_;
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

	float Edge::text_coord_x() const
	{
		return text_coord_x_;
	}

	float Edge::text_coord_y() const
	{
		return text_coord_y_;
	}
}
