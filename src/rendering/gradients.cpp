#include "gradients.h"

#include "../util.h"
#include "../math/vec4.h"

namespace kiwi {

	Gradients::Gradients(const Vertex &min_y, const Vertex &mid_y, const Vertex& max_y)
	{
		const auto one_over_dx = 1.0f /
			(((mid_y.x() - max_y.x()) *
			(min_y.y() - max_y.y())) -
				((min_y.x() - max_y.x()) *
				(mid_y.y() - max_y.y())));

		const float one_over_dy = -one_over_dx;

		// w is the perspective z value
		one_over_z_[0] = 1.0f / min_y.w();
		one_over_z_[1] = 1.0f / mid_y.w();
		one_over_z_[2] = 1.0f / max_y.w();

		text_coords_x_[0] = min_y.text_coords().x * one_over_z_[0];
		text_coords_x_[1] = mid_y.text_coords().x * one_over_z_[1];
		text_coords_x_[2] = max_y.text_coords().x * one_over_z_[2];

		text_coords_y_[0] = min_y.text_coords().y * one_over_z_[0];
		text_coords_y_[1] = mid_y.text_coords().y * one_over_z_[1];
		text_coords_y_[2] = max_y.text_coords().y * one_over_z_[2];

		depth_[0] = min_y.z();
		depth_[1] = mid_y.z();
		depth_[2] = max_y.z();

		const auto light_dir = Vec4(0.0f, 0.0f, -1.0f);
		light_[0] = clamp(min_y.normal().dot(light_dir), 0.0f, 1.0f) * 0.9f + 0.2f;
		light_[1] = clamp(mid_y.normal().dot(light_dir), 0.0f, 1.0f) * 0.9f + 0.2f;
		light_[2] = clamp(max_y.normal().dot(light_dir), 0.0f, 1.0f) * 0.9f + 0.2f;

		text_coord_xx_step_ = calc_x_step(text_coords_x_, min_y, mid_y, max_y, one_over_dx);
		text_coord_xy_step_ = calc_y_step(text_coords_x_, min_y, mid_y, max_y, one_over_dy);
		text_coord_yx_step_ = calc_x_step(text_coords_y_, min_y, mid_y, max_y, one_over_dx);
		text_coord_yy_step_ = calc_y_step(text_coords_y_, min_y, mid_y, max_y, one_over_dy);

		one_over_zx_step_ = calc_x_step(one_over_z_, min_y, mid_y, max_y, one_over_dx);
		one_over_zy_step_ = calc_y_step(one_over_z_, min_y, mid_y, max_y, one_over_dy);

		depth_x_step_ = calc_x_step(depth_, min_y, mid_y, max_y, one_over_dx);
		depth_y_step_ = calc_y_step(depth_, min_y, mid_y, max_y, one_over_dy);

		light_x_step_ = calc_x_step(light_, min_y, mid_y, max_y, one_over_dx);
		light_y_step_ = calc_y_step(light_, min_y, mid_y, max_y, one_over_dy);
	}

	float Gradients::get_text_coord_x(std::size_t index) const
	{
		return text_coords_x_[index];
	}

	float Gradients::get_text_coord_y(std::size_t index) const
	{
		return text_coords_y_[index];
	}

	float Gradients::get_depth(std::size_t index) const
	{
		return depth_[index];
	}

	float Gradients::get_light(std::size_t index) const
	{
		return light_[index];
	}

	float Gradients::get_one_over_z(std::size_t index) const
	{
		return one_over_z_[index];
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

	float Gradients::one_over_zx_step() const
	{
		return one_over_zx_step_;
	}

	float Gradients::one_over_zy_step() const
	{
		return one_over_zy_step_;
	}

	float Gradients::depth_x_step() const
	{
		return depth_x_step_;
	}

	float Gradients::depth_y_step() const
	{
		return depth_y_step_;
	}

	float Gradients::light_x_step() const
	{
		return light_x_step_;
	}

	float Gradients::light_y_step() const
	{
		return light_y_step_;
	}

	float Gradients::calc_x_step(const std::array<float, 3> values, const Vertex & min_y, const Vertex & mid_y, const Vertex & max_y, float one_over_dx)
	{
		return (((values[1] - values[2]) * (min_y.y() - max_y.y())) - ((values[0] - values[2]) * (mid_y.y() - max_y.y()))) * one_over_dx;
	}

	float Gradients::calc_y_step(const std::array<float, 3> values, const Vertex & min_y, const Vertex & mid_y, const Vertex & max_y, float one_over_dy)
	{
		return (((values[1] - values[2]) * (min_y.x() - max_y.x())) - ((values[0] - values[2]) * (mid_y.x() - max_y.x()))) * one_over_dy;
	}
}
