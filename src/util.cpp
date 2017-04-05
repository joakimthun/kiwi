#include "util.h"

#include <cstdlib>

namespace kiwi {

	float f_rand()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	TriangleAreaSign triangle_area_sign(const Vertex &min_y, const Vertex &mid_y, const Vertex &max_y)
	{
		// Vector from min to max
		float x1 = max_y.x - min_y.x;
		float y1 = max_y.y - min_y.y;

		// Vector from min to mid
		float x2 = mid_y.x - min_y.x;
		float y2 = mid_y.y - min_y.y;

		// Positive cross product, right otherwise left
		return (x1 * y2 - x2 * y1) >= 0 ? TriangleAreaSign::Positive : TriangleAreaSign::Negative;
	}

}