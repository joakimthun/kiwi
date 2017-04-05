#include "renderer.h"

#include <utility>

#include "window.h"
#include "util.h"

namespace kiwi {

	Renderer::Renderer(Window *window)
		:
		window_(window),
		width_(window->width_),
		height_(window->height_),
		back_buffer_(window->back_buffer_),
		back_buffer_size_(window->back_buffer_size_)
	{
		scan_buffer_.resize(height_ * 2);
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

	void Renderer::set_scan_buffer(int32_t y, int32_t x_min, int32_t x_max)
	{
		scan_buffer_[y * 2] = x_min;
		scan_buffer_[y * 2 + 1] = x_max;
	}

	void Renderer::fill_shape(int32_t y_min, int32_t y_max)
	{
		for (auto i = y_min; i < y_max; i++)
		{
			const auto x_min = scan_buffer_[i * 2];
			const auto x_max = scan_buffer_[i * 2 + 1];

			for (auto j = x_min; j < x_max; j++)
			{
				put_pixel(j, i, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	void Renderer::fill_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
	{
		auto min_y = v1;
		auto mid_y = v2;
		auto max_y = v3;

		// First, sort vertices by y-coord
		// If max is less then mid, swap em
		if (max_y.y < mid_y.y)
			std::swap(max_y, mid_y);

		// If mid is less then min, swap em
		if (mid_y.y < min_y.y)
			std::swap(mid_y, min_y);

		// If max is less then mid, swap em again to handle v1 being max
		if (max_y.y < mid_y.y)
			std::swap(max_y, mid_y);

		const auto area_sign = triangle_area_sign(min_y, max_y, mid_y);

		scan_convert_triangle(min_y, mid_y, max_y, static_cast<int8_t>(area_sign));
		fill_shape(static_cast<int32_t>(min_y.y), static_cast<int32_t>(max_y.y));
	}

	void Renderer::scan_convert_triangle(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, int8_t handedness)
	{
		scan_convert_line(min_y, max_y, 0 + handedness);
		scan_convert_line(min_y, mid_y, 1 - handedness);
		scan_convert_line(mid_y, max_y, 1 - handedness);
	}

	void Renderer::scan_convert_line(const Vertex &min_y, const Vertex &max_y, int8_t side)
	{
		const auto y_start = static_cast<int32_t>(min_y.y);
		const auto y_end  = static_cast<int32_t>(max_y.y);
		const auto x_start = static_cast<int32_t>(min_y.x);
		const auto x_end = static_cast<int32_t>(max_y.x);

		const auto y_dist = y_end - y_start;
		const auto x_dist = x_end - x_start;

		if (y_dist <= 0)
			return;

		// The "amount" we need to move on the x-axis for each y-coord
		const float x_stride = static_cast<float>(x_dist) / static_cast<float>(y_dist);
		float cur_x = static_cast<float>(x_start);

		for (auto i = y_start; i < y_end; i++)
		{
			scan_buffer_[i * 2 + side] = static_cast<uint32_t>(cur_x);
			cur_x += x_stride;
		}
	}

}
