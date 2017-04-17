#pragma once

namespace kiwi {

	struct Quaternion;

	struct Vec4 
	{
		Vec4();
		Vec4(float x, float y, float z);
		Vec4(float x, float y, float z, float w);

		Vec4 operator+(const Vec4 &other) const;
		Vec4 operator-(const Vec4 &other) const;
		Vec4 operator*(const Vec4 &other) const;
		Vec4 operator*(float factor) const;

		float len() const;
		Vec4 normalize() const;
		Vec4 lerp(const Vec4 &other, float amount) const;
		Vec4 cross(const Vec4 &other) const;
		float dot(const Vec4 &other) const;
		Vec4 rotate(const Quaternion &rotation);

		float x;
		float y;
		float z;
		float w;
	};

}
