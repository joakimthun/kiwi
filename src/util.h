#pragma once

#include <cstddef>
#include <stdint.h>
#include <string>
#include <vector>

#include "glm/vec4.hpp"

#include "geometry/vertex.h"

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
	glm::vec4 vec4_cross(const glm::vec4 &v1, const glm::vec4 &v2);

	std::vector<std::string> str_split(const std::string &s, char delim, RemoveEmptyEntries remove_empty_entries);

}