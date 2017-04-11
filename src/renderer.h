#pragma once

#include <stdint.h>
#include <vector>

#include "vertex.h"
#include "edge.h"

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
		void fill_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3);
		
	private:
		void scan_triangle(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, bool handedness);
		void scan_edges(const Gradients &gradients, Edge &a, Edge &b, bool handedness);
		void draw_scan_line(const Gradients &gradients, const Edge &left, const Edge &right, int32_t i);

		Window *window_;
		const int32_t width_;
		const int32_t height_;
		const float half_width_;
		const float half_height_;
		uint8_t *back_buffer_;
		const uint64_t back_buffer_size_;
	};

}