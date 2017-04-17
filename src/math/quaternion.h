#pragma once

#include "vec4.h"
#include "mat4.h"

namespace kiwi {

	struct Quaternion
	{
		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vec4 &axis, float angle);

		Quaternion operator*(const Quaternion &other) const;
		Quaternion operator*(const Vec4 &v) const;

		Quaternion conjugate() const;
		Mat4 to_rotation_matrix() const;
		float len() const;
		Quaternion normalize() const;

		Vec4 forward() const;
		Vec4 back() const;
		Vec4 up() const;
		Vec4 down() const;
		Vec4 right() const;
		Vec4 left() const;

		float x; 
		float y; 
		float z; 
		float w;
	};

}