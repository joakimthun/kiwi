#pragma once

#include <SDL.h>

#include "math/vec4.h"
#include "math/mat4.h"
#include "math/transform.h"

namespace kiwi {

	class Camera 
	{
	public:
		Camera(const Mat4 &projection);
		Camera(const Transform &transform, const Mat4 &projection);

		Mat4 view_projection() const;
		void update(SDL_Event &e, float dt);

	private:
		void move(const Vec4 &direction, float amount);
		void rotate(const Vec4 &axis, float angle);

		Transform transform_;
		Mat4 projection_;
	};

}