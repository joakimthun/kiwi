#include "vec4.h"

#include <cmath>

namespace kiwi {

	Vec4::Vec4()
		:
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{
	}

	Vec4::Vec4(float x, float y, float z, float w)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{
	}

	Vec4 Vec4::operator+(const Vec4 &other) const
	{
		return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	Vec4 Vec4::operator-(const Vec4 &other) const
	{
		return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vec4 Vec4::operator*(const Vec4 &other) const
	{
		return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	Vec4 Vec4::operator*(float factor) const
	{
		return Vec4(x * factor, y * factor, z * factor, w * factor);
	}

	float Vec4::len() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	Vec4 Vec4::normalize() const
	{
		const auto l = len();
		return Vec4(x / l, y / l, z / l, w / l);
	}

	Vec4 Vec4::lerp(const Vec4 &other, float amount) const
	{
		return (other - *this) * amount + *this;
	}

	Vec4 Vec4::cross(const Vec4 & other) const
	{
		const auto cross_x = y * other.z - z * other.y;
		const auto cross_y = z * other.x - x * other.z;
		const auto cross_z = x * other.y - y * other.x;

		return Vec4(cross_x, cross_y, cross_z, 0);
	}

}
