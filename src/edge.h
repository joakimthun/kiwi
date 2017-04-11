#pragma once

#include <stdint.h>

#include "vertex.h"

namespace kiwi {

	class Edge
	{
	public:
		Edge(const Vertex &start, const Vertex &end);

		void step();
		float x() const;
		int32_t y_start() const;
		int32_t y_end() const;

	private:
		float x_;
		float x_step_;
		int32_t y_start_;
		int32_t y_end_;
	};

}