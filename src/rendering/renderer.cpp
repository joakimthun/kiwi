#include "renderer.h"

#include <utility>
#include <math.h>
#include <float.h>

#include "../math/vec4.h"
#include "../window.h"
#include "../util.h"

namespace kiwi {

	Renderer::Renderer(Bitmap &render_target)
		:
		render_target_(render_target),
		half_width_(static_cast<float>(render_target.width() / 2)),
		half_height_(static_cast<float>(render_target.height() / 2))
	{
		depth_buffer_size_ = render_target.width() * render_target.height();
		depth_buffer_ = (float*)calloc(depth_buffer_size_, sizeof(float));
	}

	Renderer::~Renderer()
	{
		if (depth_buffer_)
		{
			free(depth_buffer_);
			depth_buffer_ = nullptr;
		}
	}

	void Renderer::clear(uint8_t r, uint8_t g, uint8_t b)
	{
		render_target_.clear(r, g, b);
	}

	void Renderer::clear_depth_buffer()
	{
		for (auto i = 0; i < depth_buffer_size_; i++)
		{
			depth_buffer_[i] = FLT_MAX;
		}
	}

	void Renderer::draw_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Bitmap &texture)
	{
		// If the triangle is completely inside the view frustum there is no need for clipping
		if (v1.inside_view_frustum() && v2.inside_view_frustum() && v3.inside_view_frustum())
		{
			fill_triangle(v1, v2, v3, texture);
			return;
		}

		VertexArray vertices;
		VertexArray result;

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);

		const std::size_t x = 0;
		const std::size_t y = 1;
		const std::size_t z = 2;

		if (clip_polygon_axis(vertices, result, x) && clip_polygon_axis(vertices, result, y) && clip_polygon_axis(vertices, result, z))
		{
			auto initial_vertex = vertices[0];

			for (int i = 1; i < vertices.size - 1; i++)
			{
				fill_triangle(initial_vertex, vertices[i], vertices[i + 1], texture);
			}
		}
	}

	void Renderer::draw_mesh(const Mesh & mesh, const Mat4 &transform, const Bitmap & texture)
	{
		for (auto i = 0; i < mesh.num_indices(); i += 3)
		{
			draw_triangle(
				mesh.get_vertex(mesh.get_index(i)).transform(transform),
				mesh.get_vertex(mesh.get_index(i + 1)).transform(transform),
				mesh.get_vertex(mesh.get_index(i + 2)).transform(transform),
				texture);
		}
	}

	bool Renderer::clip_polygon_axis(VertexArray &vertices, VertexArray &result, std::size_t component_index)
	{
		clip_polygon_component(vertices, result, component_index, 1.0f, true);
		vertices.clear();

		if (result.empty())
		{
			return false;
		}

		clip_polygon_component(result, vertices, component_index, -1.0f, false);
		result.clear();

		return !vertices.empty();
	}

	void Renderer::clip_polygon_component(VertexArray &vertices, VertexArray &result, std::size_t component_index, float component_factor, bool pos)
	{
		auto previous_vertex = vertices.back();
		auto previous_component = previous_vertex[component_index] * component_factor;
		//auto previous_inside = previous_component <= previous_vertex.w();
		bool previous_inside = false;
		if (component_index == 2 && pos)
			previous_inside = previous_component >= previous_vertex.w();
		else
			previous_inside = previous_component <= previous_vertex.w();

		for(auto i = 0; i < vertices.size; i++)
		{
			auto current_vertex = vertices[i];
			auto current_component = current_vertex[component_index] * component_factor;

			bool current_inside = false;
			if(component_index == 2 && pos)
				current_inside = current_component >= current_vertex.w();
			else
				current_inside = current_component <= current_vertex.w();

			if (current_inside != previous_inside)
			{
				auto lerp_amount = (previous_vertex.w() - previous_component) /
					((previous_vertex.w() - previous_component) -
					(current_vertex.w() - current_component));
			
				if (component_index == 2)
					lerp_amount = -lerp_amount;

				result.push_back(previous_vertex.lerp(current_vertex, lerp_amount));
			}

			if (current_inside)
			{
				result.push_back(current_vertex);
			}

			previous_vertex = current_vertex;
			previous_component = current_component;
			previous_inside = current_inside;
		}
	}

	void Renderer::fill_triangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Bitmap &texture)
	{
		auto min_y = v1.screen_space_transform(half_width_, half_height_).perspective_divide();
		auto mid_y = v2.screen_space_transform(half_width_, half_height_).perspective_divide();
		auto max_y = v3.screen_space_transform(half_width_, half_height_).perspective_divide();

		// Don't draw triangles not facing the camera
		if (triangle_area_sign(min_y, max_y, mid_y) == TriangleAreaSign::Positive)
			return;

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
		const auto depth_x_step = (right.depth() - left.depth()) / x_dist;

		auto tex_coord_x = left.text_coord_x() + tex_coord_xx_step * x_prestep;
		auto tex_coord_y = left.text_coord_y() + tex_coord_yx_step * x_prestep;
		auto one_over_z = left.one_over_z() + one_over_zx_step * x_prestep;
		auto depth = left.depth() + depth_x_step * x_prestep;

		for (auto j = min_x; j < max_x; j++)
		{
			auto depth_buffer_index = i + j * render_target_.width();

			// Only draw the pixel if it's closer to the camera than the pixel currently in the depth buffer
			if (depth < depth_buffer_[depth_buffer_index])
			{
				depth_buffer_[depth_buffer_index] = depth;
				const auto z = 1.0f / one_over_z;

				const auto src_x = static_cast<int32_t>(((tex_coord_x * z) * (float)(texture.width() - 1) + 0.5f));
				const auto src_y = static_cast<int32_t>(((tex_coord_y * z) * (float)(texture.height() - 1) + 0.5f));

				render_target_.copy_pixel(j, i, src_x, src_y, texture);
			}

			one_over_z += one_over_zx_step;
			tex_coord_x += tex_coord_xx_step;
			tex_coord_y += tex_coord_yx_step;
			depth += depth_x_step;
		}
	}
}
