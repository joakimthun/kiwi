#pragma once

#include <stdint.h>

#include "../geometry/vertex.h"
#include "gradients.h"

namespace kiwi {
	
	class Edge
	{
	public:
		Edge(const Gradients &gradients, const Vertex &min_y, const Vertex &max_y, std::size_t min_y_index);

		void step();
		float x() const;
		int32_t y_start() const;
		int32_t y_end() const;
		float text_coord_x() const;
		float text_coord_y() const;
		float one_over_z() const;
		float depth() const;
		float light() const;

	private:
		float x_;
		float x_step_;
		int32_t y_start_;
		int32_t y_end_;
		float text_coord_x_;
		float text_coord_x_step_;
		float text_coord_y_;
		float text_coord_y_step_;
		float one_over_z_;
		float one_over_z_step_;
		float depth_;
		float depth_step_;
		float light_;
		float light_step_;
	};

}