#pragma once

#include <stdint.h>
#include <vector>
#include "glm/mat4x4.hpp"

#include "geometry/vertex.h"
#include "edge.h"
#include "bitmap.h"
#include "mesh.h"

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
		void fill_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Bitmap &texture);
		void draw_mesh(const Mesh &mesh, const glm::mat4 &transform, const Bitmap &texture);
	private:
		void scan_triangle(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, bool handedness, const Bitmap &texture);
		void scan_edges(Edge &a, Edge &b, bool handedness, const Bitmap &texture);
		void draw_scan_line(const Edge &left, const Edge &right, int32_t i, const Bitmap &texture);
		void copy_pixel(int32_t dest_x, uint32_t dest_y, int32_t src_x, uint32_t src_y, const Bitmap &src);

		Window *window_;
		const int32_t width_;
		const int32_t height_;
		const float half_width_;
		const float half_height_;
		uint8_t *back_buffer_;
		const uint64_t back_buffer_size_;
	};

}