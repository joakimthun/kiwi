#include "transform.h"

namespace kiwi {

	Transform::Transform()
		:
		position_(Vec4(0.0f, 0.0f, 0.0f, 0.0f)),
		rotation_(Quaternion(0.0f, 0.0f, 0.0f, 1.0f)),
		scale_(Vec4(1.0f, 1.0f, 1.0f, 1.0f))
	{
	}

	Transform::Transform(const Vec4 &position)
		:
		position_(position),
		rotation_(Quaternion(0.0f, 0.0f, 0.0f, 1.0f)),
		scale_(Vec4(1.0f, 1.0f, 1.0f, 1.0f))
	{
	}

	Transform::Transform(const Vec4 &position, const Quaternion &rotation)
		:
		position_(position),
		rotation_(rotation),
		scale_(Vec4(1.0f, 1.0f, 1.0f, 1.0f))
	{
	}

	Transform::Transform(const Vec4 &position, const Quaternion &rotation, const Vec4 &scale)
		:
		position_(position),
		rotation_(rotation),
		scale_(scale)
	{
	}

	const Vec4 &Transform::position() const
	{
		return position_;
	}

	const Quaternion &Transform::rotation() const
	{
		return rotation_;
	}

	const Vec4 &Transform::scale() const
	{
		return scale_;
	}

	Mat4 Transform::transformation() const
	{
		const auto translation_matrix = Mat4::translation(position_.x, position_.y, position_.z);
		const auto rotation_matrix = rotation_.to_rotation_matrix();
		const auto scale_matrix = Mat4::scale(scale_.x, scale_.y, scale_.z);

		return translation_matrix * (rotation_matrix * scale_matrix);
	}

	Transform Transform::rotate(const Quaternion & rotation) const
	{
		return Transform(position_, (rotation * rotation_).normalize(), scale_);
	}

	Transform Transform::move(const Vec4 &v) const
	{
		return Transform(position_ + v, rotation_, scale_);
	}
}
