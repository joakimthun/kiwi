#pragma once

namespace kiwi {

	constexpr double PI = 3.14159265358979323846;

	constexpr inline float degrees_to_radians(float degrees)
	{
		return (degrees * static_cast<float>(PI)) / 180;
	}

	constexpr inline float radians_to_degrees(float radians)
	{
		return (radians * 180) / static_cast<float>(PI);
	}

}