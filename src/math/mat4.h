#pragma once

#include <array>

#include "vec4.h"

namespace kiwi {

	struct Mat4
	{
		static Mat4 identity();
		static Mat4 translation(float x, float y, float z);
		static Mat4 perspective(float fov, float aspect_ratio, float near_plane, float far_plane);
		static Mat4 rotation(float x, float y, float z);

		Mat4 operator*(const Mat4 &other) const;
		Vec4 operator*(const Vec4 &v) const;

		std::array<std::array<float, 4>, 4> values;

	private:
		Mat4();
	};

}
