#include <iostream>

#include "util.h"
#include "window.h"
#include "rendering/renderer.h"
#include "geometry/vertex.h"
#include "rendering/bitmap.h"
#include "geometry/mesh.h"

#include "math/util.h"
#include "math/vec4.h"
#include "math/mat4.h"

using namespace kiwi;

// TODO: Use a real timer...
const float dt = 0.0016f;

int main(int argc, char* argv[])
{
	Window window(800, 600);
	window.open();

	Renderer renderer(window.display_buffer());

	const auto mesh = Mesh("assets/monkey0.obj");

	auto texture = Bitmap(512, 512);
	for (auto j = 0; j < texture.height(); j++)
	{
		for (auto i = 0; i < texture.width(); i++)
		{
			texture.put_pixel(i, j,
				static_cast<uint8_t>(f_rand() * 255.0 + 0.5),
				static_cast<uint8_t>(f_rand() * 255.0 + 0.5),
				static_cast<uint8_t>(f_rand() * 255.0 + 0.5));
		}
	}

	Vertex minYVert = Vertex(Vec4(-1, -1, 0, 1),
		Vec4(0.0f, 0.0f, 0.0f, 0.0f));
	Vertex midYVert = Vertex(Vec4(0, 1, 0, 1),
		Vec4(0.5f, 1.0f, 0.0f, 0.0f));
	Vertex maxYVert = Vertex(Vec4(1, -1, 0, 1),
		Vec4(1.0f, 0.0f, 0.0f, 0.0f));

	const auto projection = Mat4::perspective(degrees_to_radians(70.0f),800.f / 600.f, 0.1f, 1000.0f);
	const auto translation = Mat4::translation(0.0f, 0.0f, 4.0f);

	float rotation_v = 0.0f;

	MSG msg = { 0 };
	while (1)
	{
		while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		renderer.clear(0x00, 0x00, 0x00);
		renderer.clear_depth_buffer();

		rotation_v += dt * 5.5f;
		const auto rotation = Mat4::rotation(0.0f, rotation_v, 0.0f);
		const auto transform = projection * translation * rotation;

		renderer.draw_mesh(mesh, transform, texture);

		window.update();
	}

	return 0;
}