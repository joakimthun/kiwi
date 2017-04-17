#include "mat4.h"

#include <math.h>

namespace kiwi {

	Mat4 Mat4::identity()
	{
		auto m = Mat4();

		m.values[0][0] = 1;	m.values[0][1] = 0;	m.values[0][2] = 0;	m.values[0][3] = 0;
		m.values[1][0] = 0;	m.values[1][1] = 1;	m.values[1][2] = 0;	m.values[1][3] = 0;
		m.values[2][0] = 0;	m.values[2][1] = 0;	m.values[2][2] = 1;	m.values[2][3] = 0;
		m.values[3][0] = 0;	m.values[3][1] = 0;	m.values[3][2] = 0;	m.values[3][3] = 1;

		return m;
	}

	Mat4 Mat4::translation(float x, float y, float z)
	{
		auto m = Mat4();

		m.values[0][0] = 1;	m.values[0][1] = 0;	m.values[0][2] = 0;	m.values[0][3] = x;
		m.values[1][0] = 0;	m.values[1][1] = 1;	m.values[1][2] = 0;	m.values[1][3] = y;
		m.values[2][0] = 0;	m.values[2][1] = 0;	m.values[2][2] = 1;	m.values[2][3] = z;
		m.values[3][0] = 0;	m.values[3][1] = 0;	m.values[3][2] = 0;	m.values[3][3] = 1;

		return m;
	}

	Mat4 Mat4::scale(float x, float y, float z)
	{
		auto m = Mat4();

		m.values[0][0] = x;	m.values[0][1] = 0;	m.values[0][2] = 0;	m.values[0][3] = 0;
		m.values[1][0] = 0;	m.values[1][1] = y;	m.values[1][2] = 0;	m.values[1][3] = 0;
		m.values[2][0] = 0;	m.values[2][1] = 0;	m.values[2][2] = z;	m.values[2][3] = 0;
		m.values[3][0] = 0;	m.values[3][1] = 0;	m.values[3][2] = 0;	m.values[3][3] = 1;

		return m;
	}

	Mat4 Mat4::perspective(float fov, float aspect_ratio, float near_plane, float far_plane)
	{
		auto m = Mat4();

		const auto tan_half_fov = std::tan(fov / 2);
		const auto range = near_plane - far_plane;

		m.values[0][0] = 1.0f / (tan_half_fov * aspect_ratio);	m.values[0][1] = 0;		
		m.values[1][0] = 0;										m.values[1][1] = 1.0f / tan_half_fov;
		m.values[2][0] = 0;										m.values[2][1] = 0;
		m.values[3][0] = 0;										m.values[3][1] = 0;

		m.values[0][2] = 0;										m.values[0][3] = 0;
		m.values[1][2] = 0;										m.values[1][3] = 0;
		m.values[2][2] = (-near_plane - far_plane) / range;		m.values[2][3] = 2 * far_plane * near_plane / range;
		m.values[3][2] = 1;										m.values[3][3] = 0;

		return m;
	}

	Mat4 Mat4::rotation(float x, float y, float z)
	{
		auto rx = Mat4();
		auto ry = Mat4();
		auto rz = Mat4();

		const auto cos_x = std::cos(x);
		const auto sin_x = std::sin(x);
		const auto cos_y = std::cos(y);
		const auto sin_y = std::sin(y);
		const auto cos_z = std::cos(z);
		const auto sin_z = std::sin(z);

		rz.values[0][0] = cos_z;	rz.values[0][1] = -sin_z;	rz.values[0][2] = 0;		rz.values[0][3] = 0;
		rz.values[1][0] = sin_z;	rz.values[1][1] = cos_z;	rz.values[1][2] = 0;		rz.values[1][3] = 0;
		rz.values[2][0] = 0;		rz.values[2][1] = 0;		rz.values[2][2] = 1;		rz.values[2][3] = 0;
		rz.values[3][0] = 0;		rz.values[3][1] = 0;		rz.values[3][2] = 0;		rz.values[3][3] = 1;

		rx.values[0][0] = 1;		rx.values[0][1] = 0;		rx.values[0][2] = 0;		rx.values[0][3] = 0;
		rx.values[1][0] = 0;		rx.values[1][1] = cos_x;	rx.values[1][2] = -sin_x;	rx.values[1][3] = 0;
		rx.values[2][0] = 0;		rx.values[2][1] = sin_x;	rx.values[2][2] = cos_x;	rx.values[2][3] = 0;
		rx.values[3][0] = 0;		rx.values[3][1] = 0;		rx.values[3][2] = 0;		rx.values[3][3] = 1;

		ry.values[0][0] = cos_y;	ry.values[0][1] = 0;		ry.values[0][2] = -sin_y;	ry.values[0][3] = 0;
		ry.values[1][0] = 0;		ry.values[1][1] = 1;		ry.values[1][2] = 0;		ry.values[1][3] = 0;
		ry.values[2][0] = sin_y;	ry.values[2][1] = 0;		ry.values[2][2] = cos_y;	ry.values[2][3] = 0;
		ry.values[3][0] = 0;		ry.values[3][1] = 0;		ry.values[3][2] = 0;		ry.values[3][3] = 1;

		return  rz * (ry * rx);
	}

	Mat4 Mat4::rotation(const Vec4 &forward, const Vec4 &up, const Vec4 &right)
	{
		auto m = Mat4();

		m.values[0][0] = right.x;	m.values[0][1] = right.y;	m.values[0][2] = right.z;	m.values[0][3] = 0;
		m.values[1][0] = up.x;		m.values[1][1] = up.y;		m.values[1][2] = up.z;		m.values[1][3] = 0;
		m.values[2][0] = forward.x;	m.values[2][1] = forward.y;	m.values[2][2] = forward.z;	m.values[2][3] = 0;
		m.values[3][0] = 0;			m.values[3][1] = 0;			m.values[3][2] = 0;			m.values[3][3] = 1;

		return m;
	}

	Mat4 Mat4::operator*(const Mat4 &other) const
	{
		auto m = Mat4();

		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				m.values[i][j] = 
					values[i][0] * other.values[0][j] + 
					values[i][1] * other.values[1][j] + 
					values[i][2] * other.values[2][j] + 
					values[i][3] * other.values[3][j];
			}
		}

		return m;
	}

	Vec4 Mat4::operator*(const Vec4 &v) const
	{
		return Vec4(
			values[0][0] * v.x + values[0][1] * v.y + values[0][2] * v.z + values[0][3] * v.w,
			values[1][0] * v.x + values[1][1] * v.y + values[1][2] * v.z + values[1][3] * v.w,
			values[2][0] * v.x + values[2][1] * v.y + values[2][2] * v.z + values[2][3] * v.w,
			values[3][0] * v.x + values[3][1] * v.y + values[3][2] * v.z + values[3][3] * v.w);
	}

	Mat4::Mat4()
	{
		values[0][0] = 0;	values[0][1] = 0;	values[0][2] = 0;	values[0][3] = 0;
		values[1][0] = 0;	values[1][1] = 0;	values[1][2] = 0;	values[1][3] = 0;
		values[2][0] = 0;	values[2][1] = 0;	values[2][2] = 0;	values[2][3] = 0;
		values[3][0] = 0;	values[3][1] = 0;	values[3][2] = 0;	values[3][3] = 0;
	}

}
