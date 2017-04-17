#include "quaternion.h"

#include <cmath>

namespace kiwi {

	Quaternion::Quaternion()
		:
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{
	}

	Quaternion::Quaternion(float x, float y, float z, float w)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{
	}

	Quaternion::Quaternion(const Vec4 &axis, float angle)
	{
		const auto sin_half_angle = std::sin(angle / 2);
		const auto cos_half_angle = std::cos(angle / 2);

		x = axis.x * sin_half_angle;
		y = axis.y * sin_half_angle;
		z = axis.z * sin_half_angle;
		w = cos_half_angle;
	}

	Quaternion Quaternion::operator*(const Quaternion &other) const
	{
		const auto w_ = w * other.w - x * other.x - y * other.y - z * other.z;
		const auto x_ = x * other.w + w * other.x + y * other.z - z * other.y;
		const auto y_ = y * other.w + w * other.y + z * other.x - x * other.z;
		const auto z_ = z * other.w + w * other.z + x * other.y - y * other.x;

		return Quaternion(x_, y_, z_, w_);
	}

	Quaternion Quaternion::operator*(const Vec4 & v) const
	{
		const auto w_ = -x * v.x - y * v.y - z * v.z;
		const auto x_ = w * v.x + y * v.z - z * v.y;
		const auto y_ = w * v.y + z * v.x - x * v.z;
		const auto z_ = w * v.z + x * v.y - y * v.x;

		return Quaternion(x_, y_, z_, w_);
	}

	Quaternion Quaternion::conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Mat4 Quaternion::to_rotation_matrix() const
	{
		const auto forward = Vec4(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
		const auto up = Vec4(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
		const auto right = Vec4(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));

		return Mat4::rotation(forward, up, right);
	}

	float Quaternion::len() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	Quaternion Quaternion::normalize() const
	{
		const auto l = len();
		return Quaternion(x / l, y / l, z / l, w / l);
	}

	Vec4 Quaternion::forward() const
	{
		return Vec4(0.0f, 0.0f, 1.0f, 1.0f).rotate(*this);
	}

	Vec4 Quaternion::back() const
	{
		return Vec4(0.0f, 0.0f, -1.0f, 1.0f).rotate(*this);
	}

	Vec4 Quaternion::up() const
	{
		return Vec4(0.0f, 1.0f, 0.0f, 1.0f).rotate(*this);
	}

	Vec4 Quaternion::down() const
	{
		return Vec4(0.0f, -1.0f, 0.0f, 1.0f).rotate(*this);
	}

	Vec4 Quaternion::right() const
	{
		return Vec4(1.0f, 0.0f, 0.0f, 1.0f).rotate(*this);
	}

	Vec4 Quaternion::left() const
	{
		return Vec4(-1.0f, 0.0f, 0.0f, 1.0f).rotate(*this);
	}

}
