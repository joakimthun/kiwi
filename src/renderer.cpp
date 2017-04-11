#include "renderer.h"

#include <utility>
#include <math.h>
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
		auto top_to_bottom = Edge(min_y, max_y);
		auto top_to_middle = Edge(min_y, mid_y);
		auto middle_to_bottom = Edge(mid_y, max_y);

		scan_edges(top_to_bottom, top_to_middle, handedness);
		scan_edges(top_to_bottom, middle_to_bottom, handedness);
	}

	void Renderer::scan_edges(Edge &a, Edge &b, bool handedness)
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
			draw_scan_line(left->x(), right->x(), i);
			left->step();
			right->step();
		}
	}

	void Renderer::draw_scan_line(float x_min, float x_max, int32_t i)
	{
		const auto min_x = static_cast<int32_t>(ceil(x_min));
		const auto max_x = static_cast<int32_t>(ceil(x_max));

		for (auto j = min_x; j < max_x; j++)
		{
			put_pixel(j, i, 0xFF, 0xFF, 0xFF);
		}
	}

}
