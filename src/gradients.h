#pragma once

#include <array>

#include "vertex.h"

namespace kiwi {

	class Gradients
	{
	public:
		Gradients(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y);

		const float get_text_coord_x(std::size_t index) const;
		const float get_text_coord_y(std::size_t index) const;
		float text_coord_xx_step() const;
		float text_coord_xy_step() const;
		float text_coord_yx_step() const;
		float text_coord_yy_step() const;

	private:
		std::array<float, 3> text_coords_x_;
		std::array<float, 3> text_coords_y_;
		float text_coord_xx_step_;
		float text_coord_xy_step_;
		float text_coord_yx_step_;
		float text_coord_yy_step_;
	};

}