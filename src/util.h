#pragma once

#include <cstddef>
#include <stdint.h>

#include "vertex.h"

namespace kiwi {
	
	enum class TriangleAreaSign : int8_t 
	{
		Positive = 0,
		Negative = 1
	};

	float f_rand();
	TriangleAreaSign triangle_area_sign(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y);

}