#pragma once

#include <cstddef>
#include <stdint.h>
#include <string>
#include <vector>

#include "glm/vec4.hpp"

#include "vertex.h"

namespace kiwi {
	
	enum class TriangleAreaSign : int8_t 
	{
		Positive = 0,
		Negative = 1
	};

	enum class RemoveEmptyEntries : int8_t
	{
		No = 0,
		Yes = 1
	};

	float f_rand();
	TriangleAreaSign triangle_area_sign(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y);

	std::vector<std::string> str_split(const std::string &s, char delim, RemoveEmptyEntries remove_empty_entries);

}