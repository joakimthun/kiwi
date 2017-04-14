#include "renderer.h"

#include <utility>
#include <math.h>
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#include "window.h"
#include "util.h"

namespace kiwi {

	Renderer::Renderer(Window *window)
		:
		window_(window),
		width_(window->width_),
		height_(window->height_),
		half_width_(static_cast<float>(width_ / 2)),
		half_height_(static_cast<float>(height_ / 2)),
		back_buffer_(window->back_buffer_),
		back_buffer_size_(window->back_buffer_size_)
	{
	}

	int32_t Renderer::width()
	{
		return width_;
	}

	int32_t Renderer::height()
	{
		return height_;
	}

	void Renderer::clear(uint8_t r, uint8_t g, uint8_t b)
	{
		for (auto i = 0; i < back_buffer_size_; i += 3)
		{
			back_buffer_[i] = b;
			back_buffer_[i + 1] = g;
			back_buffer_[i + 2] = r;
		}
	}

	void Renderer::put_pixel(int32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
	{
		int index = (x + y * width_) * 3;
		back_buffer_[index] = b;
		back_buffer_[index + 1] = g;
		back_buffer_[index + 2] = r;
	}

	void Renderer::fill_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Bitmap &texture)
	{
		auto min_y = v1.screen_space_transform(half_width_, half_height_).perspective_divide();
		auto mid_y = v2.screen_space_transform(half_width_, half_height_).perspective_divide();
		auto max_y = v3.screen_space_transform(half_width_, half_height_).perspective_divide();

		// First, sort vertices by y-coord
		// If max is less then mid, swap em
		if (max_y.y() < mid_y.y())
			std::swap(max_y, mid_y);

		// If mid is less then min, swap em
		if (mid_y.y() < min_y.y())
			std::swap(mid_y, min_y);

		// If max is less then mid, swap em again to handle v1 being max
		if (max_y.y() < mid_y.y())
			std::swap(max_y, mid_y);

		const auto area_sign = triangle_area_sign(min_y, max_y, mid_y);

		scan_triangle(min_y, mid_y, max_y, area_sign == TriangleAreaSign::Positive, texture);
	}

	void Renderer::scan_triangle(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, bool handedness, const Bitmap &texture)
	{
		const auto gradients = Gradients(min_y, mid_y, max_y);

		auto top_to_bottom = Edge(gradients, min_y, max_y, 0);
		auto top_to_middle = Edge(gradients, min_y, mid_y, 0);
		auto middle_to_bottom = Edge(gradients, mid_y, max_y, 1);

		scan_edges(top_to_bottom, top_to_middle, handedness, texture);
		scan_edges(top_to_bottom, middle_to_bottom, handedness, texture);
	}

	void Renderer::scan_edges(Edge &a, Edge &b, bool handedness, const Bitmap &texture)
	{
		auto *left = &a;
		auto *right = &b;

		if (handedness)
		{
			std::swap(left, right);
		}

		const auto y_start = b.y_start();
		const auto y_end = b.y_end();

		for (auto i = y_start; i < y_end; i++)
		{
			draw_scan_line(*left, *right, i, texture);
			left->step();
			right->step();
		}
	}

	void Renderer::draw_scan_line(const Edge &left, const Edge &right, int32_t i, const Bitmap &texture)
	{
		const auto min_x = static_cast<int32_t>(ceil(left.x()));
		const auto max_x = static_cast<int32_t>(ceil(right.x()));
		const auto x_prestep = min_x - left.x();

		const auto x_dist = right.x() - left.x();

		const auto tex_coord_xx_step = (right.text_coord_x() - left.text_coord_x()) / x_dist;
		const auto tex_coord_yx_step = (right.text_coord_y() - left.text_coord_y()) / x_dist;
		const auto one_over_zx_step = (right.one_over_z() - left.one_over_z()) / x_dist;

		auto tex_coord_x = left.text_coord_x() + tex_coord_xx_step * x_prestep;
		auto tex_coord_y = left.text_coord_y() + tex_coord_yx_step * x_prestep;
		auto one_over_z = left.one_over_z() + one_over_zx_step * x_prestep;

		for (auto j = min_x; j < max_x; j++)
		{
			const auto z = 1.0f / one_over_z;

			const auto src_x = static_cast<int32_t>(((tex_coord_x * z) * (float)(texture.width() - 1) + 0.5f));
			const auto src_y = static_cast<int32_t>(((tex_coord_y * z) * (float)(texture.height() - 1) + 0.5f));

			copy_pixel(j, i, src_x, src_y, texture);

			one_over_z += one_over_zx_step;
			tex_coord_x += tex_coord_xx_step;
			tex_coord_y += tex_coord_yx_step;
		}
	}

	void Renderer::copy_pixel(int32_t dest_x, uint32_t dest_y, int32_t src_x, uint32_t src_y, const Bitmap& src)
	{
		const auto dest_index = (dest_x + dest_y * width_) * 3;
		const auto src_index = (src_x + src_y * src.width()) * 3;
		back_buffer_[dest_index] = src.get_component(src_index);
		back_buffer_[dest_index + 1] = src.get_component(src_index + 1);
		back_buffer_[dest_index + 2] = src.get_component(src_index + 2);
	}

}
