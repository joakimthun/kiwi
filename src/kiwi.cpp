#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "kiwi_exception.h"
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

void init_sdl();

// TODO: Use a real timer...
const float dt = 0.0032f;

int main(int argc, char* argv[])
{
	init_sdl();

	auto texture = Bitmap("assets/alduin.jpg");

	auto window = create_window(1920, 1080);
	window->open();

	auto renderer = Renderer(window->display_buffer());

	const auto mesh = Mesh("assets/alduin.obj");
	auto transform = Transform(Vec4(0.0f, -10.0f, 10.0f), Quaternion(Vec4(0.0f, 1.0f, 0.0f), 2.0f), Vec4(0.05f, 0.05f, 0.05f));

	const auto camera_transform = Transform(Vec4(0.0f, 20.0f, -30.0f), Quaternion(Vec4(1.0f, 0.0f, 0.0f), degrees_to_radians(40.0f)));
	auto camera = Camera(camera_transform, Mat4::perspective(degrees_to_radians(70.0f), static_cast<float>(window->width()) / static_cast<float>(window->height()), 0.1f, 1000.0f));

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

		renderer.clear(0xF6, 0xF6, 0xF6);
		renderer.clear_depth_buffer();

		const auto vp = camera.view_projection();

		//transform = transform.rotate(Quaternion(Vec4(0.0f, 1.0f, 0.0f), dt * 3.0f));

		renderer.draw_mesh(mesh, vp, transform.transformation(), texture);

		window->update();
	}

	return 0;
}

void init_sdl()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw KiwiException("SDL_INIT_VIDEO failed: " + std::string(SDL_GetError()));

	const auto img_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if (!(IMG_Init(img_flags) & img_flags))
		throw KiwiException("SDL_IMG_Init failed: " + std::string(IMG_GetError()));
}