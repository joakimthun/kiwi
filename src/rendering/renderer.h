#pragma once

#include <stdint.h>
#include <vector>
#include <array>

#include "../math/mat4.h"
#include "../geometry/vertex.h"
#include "edge.h"
#include "bitmap.h"
#include "../geometry/mesh.h"

namespace kiwi {

	class Renderer
	{
	public:
		Renderer(Bitmap &render_target);
		~Renderer();

		void clear(uint8_t r, uint8_t g, uint8_t b);
		void clear_depth_buffer();
		void draw_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Bitmap &texture);
		void draw_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Mat4 &view_projection, const Mat4 &transform, const Bitmap &texture);
		void draw_mesh(const Mesh &mesh, const Mat4 &view_projection, const Mat4 &transform, const Bitmap &texture);
		void set_light_direction(const Vec4 &direction);
		void set_ambient_lighting_intensity(float intensity);
		
	private:
		bool clip_polygon_axis(std::vector<Vertex> &vertices, std::vector<Vertex> &result, std::size_t component_index);
		void clip_polygon_component(std::vector<Vertex> &vertices, std::vector<Vertex> &result, std::size_t component_index, float component_factor);
		void fill_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Bitmap &texture);
		void scan_triangle(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y, bool handedness, const Bitmap &texture);
		void scan_edges(const Gradients &gradients, Edge &a, Edge &b, bool handedness, const Bitmap &texture);
		void draw_scan_line(const Gradients &gradients, const Edge &left, const Edge &right, int32_t i, const Bitmap &texture);

		Bitmap &render_target_;
		float* depth_buffer_;
		std::size_t depth_buffer_size_;
		const float half_width_;
		const float half_height_;
		Vec4 light_direction_;
		float ambient_lighting_intensity_;
	};

}