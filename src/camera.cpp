#include "camera.h"

#include "math/quaternion.h"

namespace kiwi {

	Camera::Camera(const Mat4 &projection)
		:
		projection_(projection)
	{
	}

	Camera::Camera(const Transform &transform, const Mat4 & projection)
		:
		transform_(transform),
		projection_(projection)
	{
	}

	Mat4 Camera::view_projection() const
	{
		const auto camera_rotation = transform_.rotation().conjugate().to_rotation_matrix();
		const auto camera_position = transform_.position() * -1.0f;
		const auto camera_translation = Mat4::translation(camera_position.x, camera_position.y, camera_position.z);

		return projection_ * (camera_rotation * camera_translation);
	}

	const auto Y_AXIS_VECTOR = Vec4(0, 1, 0);

	void Camera::update(SDL_Event &e, float dt)
	{
		const auto rotation = transform_.rotation();
		const auto mw_move_amount = 50.0f * dt;
		const auto move_amount = 220.0f * dt;
		const auto x_amount = 2.0f * dt;
		const auto y_amount = 2.0f * dt;

		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_a:
				move(rotation.left(), move_amount);
				break;
			case SDLK_d:
				move(rotation.right(), move_amount);
				break;
			case SDLK_w:
				move(rotation.forward(), move_amount);
				break;
			case SDLK_s:
				move(rotation.back(), move_amount);
				break;
			case SDLK_LEFT:
				rotate(Y_AXIS_VECTOR, -x_amount);
				break;
			case SDLK_RIGHT:
				rotate(Y_AXIS_VECTOR, x_amount);
				break;
			case SDLK_UP:
				rotate(rotation.right(), -y_amount);
				break;
			case SDLK_DOWN:
				rotate(rotation.right(), y_amount);
				break;
			}
		}
		else if (e.type == SDL_MOUSEWHEEL)
		{
			if (e.wheel.y >= 0)
			{
				move(rotation.forward(), mw_move_amount);
			}
			else
			{
				move(rotation.back(), mw_move_amount);
			}
		}
	}

	void Camera::move(const Vec4 &direction, float amount)
	{
		transform_ = transform_.move(direction * amount);
	}

	void Camera::rotate(const Vec4 &axis, float angle)
	{
		transform_ = transform_.rotate(Quaternion(axis, angle));
	}

}
