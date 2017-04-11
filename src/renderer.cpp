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

	void Renderer::fill_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
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

		scan_triangle(min_y, mid_y, max_y, area_sign == TriangleAreaSign::Positive);
	}

	void Renderer::scan_triangle(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, bool handedness)
	{
		const auto gradients = Gradients(min_y, mid_y, max_y);

		auto top_to_bottom = Edge(gradients, min_y, max_y, 0);
		auto top_to_middle = Edge(gradients, min_y, mid_y, 0);
		auto middle_to_bottom = Edge(gradients, mid_y, max_y, 1);

		scan_edges(gradients, top_to_bottom, top_to_middle, handedness);
		scan_edges(gradients, top_to_bottom, middle_to_bottom, handedness);
	}

	void Renderer::scan_edges(const Gradients &gradients, Edge &a, Edge &b, bool handedness)
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
			draw_scan_line(gradients, *left, *right, i);
			left->step();
			right->step();
		}
	}

	void Renderer::draw_scan_line(const Gradients &gradients, const Edge &left, const Edge &right, int32_t i)
	{
		const auto min_x = static_cast<int32_t>(ceil(left.x()));
		const auto max_x = static_cast<int32_t>(ceil(right.x()));

		auto x_prestep = min_x - left.x();
		const auto color_x_step = gradients.color_x_step();
		auto color = left.color() + (color_x_step * x_prestep);

		for (auto j = min_x; j < max_x; j++)
		{
			// Colors are in the 0.0  1.0 range
			const auto r = static_cast<uint8_t>(color.x * 255.0f + 0.5f);
			const auto g = static_cast<uint8_t>(color.y * 255.0f + 0.5f);
			const auto b = static_cast<uint8_t>(color.z * 255.0f + 0.5f);

			put_pixel(j, i, r, g, b);
			color = color + color_x_step;
		}
	}

}
