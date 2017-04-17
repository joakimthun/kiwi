#pragma once

#include "vec4.h"
#include "mat4.h"
#include "quaternion.h"

namespace kiwi {

	class Transform
	{
	public:
		Transform();
		Transform(const Vec4 &position);
		Transform(const Vec4 &position, const Quaternion &rotation);
		Transform(const Vec4 &position, const Quaternion &rotation, const Vec4 &scale);

		const Vec4 &position() const;
		const Quaternion &rotation() const;
		const Vec4 &scale() const;
		Mat4 transformation() const;

		Transform rotate(const Quaternion &rotation) const;
		Transform move(const Vec4 &v) const;

	private:
		Vec4 position_;
		Quaternion rotation_;
		Vec4 scale_;
	};

}
