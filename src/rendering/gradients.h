#pragma once

#include <array>

#include "../math/vec4.h"
#include "../geometry/vertex.h"

namespace kiwi {

	class Gradients
	{
	public:
		Gradients(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, const Vec4 &light_direction, float ambient_lighting_intensity);

		float get_text_coord_x(std::size_t index) const;
		float get_text_coord_y(std::size_t index) const;
		float get_one_over_z(std::size_t index) const;
		float get_depth(std::size_t index) const;
		float get_light(std::size_t index) const;

		float text_coord_xx_step() const;
		float text_coord_xy_step() const;
		float text_coord_yx_step() const;
		float text_coord_yy_step() const;
		float one_over_zx_step() const;
		float one_over_zy_step() const;
		float depth_x_step() const;
		float depth_y_step() const;
		float light_x_step() const;
		float light_y_step() const;

	private:
		float calc_x_step(const std::array<float, 3> values, const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, float one_over_dx);
		float calc_y_step(const std::array<float, 3> values, const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, float one_over_dy);

		std::array<float, 3> text_coords_x_;
		std::array<float, 3> text_coords_y_;
		std::array<float, 3> one_over_z_;
		std::array<float, 3> depth_;
		std::array<float, 3> light_;

		float text_coord_xx_step_;
		float text_coord_xy_step_;
		float text_coord_yx_step_;
		float text_coord_yy_step_;
		float one_over_zx_step_;
		float one_over_zy_step_;
		float depth_x_step_;
		float depth_y_step_;
		float light_x_step_;
		float light_y_step_;
	};

}