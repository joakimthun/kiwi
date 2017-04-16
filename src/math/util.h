#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace kiwi {

	constexpr inline float degrees_to_radians(float degrees)
	{
		return (degrees * static_cast<float>(M_PI)) / 180;
	}

	constexpr inline float radians_to_degrees(float radians)
	{
		return (radians * 180) / static_cast<float>(M_PI);
	}

}