#include "gradients.h"

namespace kiwi {

	Gradients::Gradients(const Vertex &min_y, const Vertex &mid_y, const Vertex& max_y)
	{
		const auto one_over_dx = 1.0f /
			(((mid_y.x() - max_y.x()) *
			(min_y.y() - max_y.y())) -
				((min_y.x() - max_y.x()) *
				(mid_y.y() - max_y.y())));

		const float one_over_dy = -one_over_dx;

		text_coords_x_[0] = min_y.text_coords().x;
		text_coords_x_[1] = mid_y.text_coords().x;
		text_coords_x_[2] = max_y.text_coords().x;

		text_coords_y_[0] = min_y.text_coords().y;
		text_coords_y_[1] = mid_y.text_coords().y;
		text_coords_y_[2] = max_y.text_coords().y;

		text_coord_xx_step_ =
			(((text_coords_x_[1] - text_coords_x_[2]) *
			(min_y.y() - max_y.y())) -
				((text_coords_x_[0] - text_coords_x_[2]) *
				(mid_y.y() - max_y.y()))) * one_over_dx;

		text_coord_xy_step_ =
			(((text_coords_x_[1] - text_coords_x_[2]) *
			(min_y.x() - max_y.x())) -
				((text_coords_x_[0] - text_coords_x_[2]) *
				(mid_y.x() - max_y.x()))) * one_over_dy;

		text_coord_yx_step_ =
			(((text_coords_y_[1] - text_coords_y_[2]) *
			(min_y.y() - max_y.y())) -
				((text_coords_y_[0] - text_coords_y_[2]) *
				(mid_y.y() - max_y.y()))) * one_over_dx;

		text_coord_yy_step_ =
			(((text_coords_y_[1] - text_coords_y_[2]) *
			(min_y.x() - max_y.x())) -
				((text_coords_y_[0] - text_coords_y_[2]) *
				(mid_y.x() - max_y.x()))) * one_over_dy;
	}

	const float Gradients::get_text_coord_x(std::size_t index) const
	{
		return text_coords_x_[index];
	}

	const float Gradients::get_text_coord_y(std::size_t index) const
	{
		return text_coords_y_[index];
	}

	float Gradients::text_coord_xx_step() const
	{
		return text_coord_xx_step_;
	}

	float Gradients::text_coord_xy_step() const
	{
		return text_coord_xy_step_;
	}

	float Gradients::text_coord_yx_step() const
	{
		return text_coord_yx_step_;
	}

	float Gradients::text_coord_yy_step() const
	{
		return text_coord_yy_step_;
	}
}
