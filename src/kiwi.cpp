#include <SDL.h>
#include <iostream>

#include "util.h"
#include "window.h"
#include "rendering/renderer.h"
#include "geometry/vertex.h"
#include "rendering/bitmap.h"
#include "geometry/mesh.h"
#include "camera.h"

#include "math/util.h"
#include "math/vec4.h"
#include "math/mat4.h"

#include "math/transform.h"
#include "math/quaternion.h"

using namespace kiwi;

// TODO: Use a real timer...
const float dt = 0.0032f;

int main(int argc, char* argv[])
{
	auto window = create_window(800, 600);
	window->open();

	auto renderer = Renderer(window->display_buffer());

	const auto monkey_mesh = Mesh("assets/monkey0.obj");
	auto monkey_transform = Transform(Vec4(0.0f, 1.0f, 3.0f));

	const auto terrain_mesh = Mesh("assets/terrain2.obj");
	const auto terrain_transform = Transform(Vec4(0.0f, -1.0f, 0.0f));

	auto texture = Bitmap(512, 512);
	for (auto j = 0; j < texture.height(); j++)
	{
		for (auto i = 0; i < texture.width(); i++)
		{
			texture.put_pixel(i, j,
				//static_cast<uint8_t>(f_rand() * 255.0 + 0.5),
				//static_cast<uint8_t>(f_rand() * 255.0 + 0.5),
				//static_cast<uint8_t>(f_rand() * 255.0 + 0.5));
				static_cast<uint8_t>(220.0f),
				static_cast<uint8_t>(220.0f),
				static_cast<uint8_t>(220.0f));
		}
	}

	const auto camera_transform = Transform(Vec4(0.0f, 5.0f, -3.0f), Quaternion( Vec4(1.0f, 0.0f, 0.0f), degrees_to_radians(30.0f)));
	auto camera = Camera(camera_transform, Mat4::perspective(degrees_to_radians(70.0f),800.f / 600.f, 0.1f, 1000.0f));

	auto running = true;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				running = false;
			}

			camera.update(e, dt);
		}

		renderer.clear(0xFF, 0x00, 0x00);
		renderer.clear_depth_buffer();

		const auto vp = camera.view_projection();

		monkey_transform = monkey_transform.rotate(Quaternion(Vec4(0.0f, 1.0f, 0.0f), dt * 5.0f));

		renderer.draw_mesh(monkey_mesh, vp, monkey_transform.transformation(), texture);
		renderer.draw_mesh(terrain_mesh, vp, terrain_transform.transformation(), texture);

		window->update();
	}

	return 0;
}