#pragma once

#include <stdint.h>
#include <vector>

#include "vertex.h"

namespace kiwi {

	class Window;

	class Renderer
	{
	public:
		Renderer(Window *window);


		int32_t width();
		int32_t height();
		void clear(uint8_t r, uint8_t g, uint8_t b);
		void put_pixel(int32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
		void set_scan_buffer(int32_t y, int32_t x_min, int32_t x_max);
		void fill_shape(int32_t y_min, int32_t y_max);
		void scan_convert_triangle(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, int8_t handedness);
	private:
		void scan_convert_line(const Vertex &min_y, const Vertex &max_y, int8_t side);

		Window *window_;
		int32_t width_;
		int32_t height_;
		uint8_t *back_buffer_;
		const uint64_t back_buffer_size_;
		std::vector<uint32_t> scan_buffer_;
	};

}