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
#include "timer.h"

#include "math/util.h"
#include "math/vec4.h"
#include "math/mat4.h"

#include "math/transform.h"
#include "math/quaternion.h"

using namespace kiwi;

void init_sdl();

int main(int argc, char* argv[])
{
	init_sdl();

	auto texture = Bitmap("assets/alduin.jpg");

	auto window = create_window(1280, 720);
	window->open();

	auto renderer = Renderer(window->display_buffer());

	const auto mesh = Mesh("assets/alduin.obj");
	auto transform = Transform(Vec4(0.0f, -10.0f, 10.0f), Quaternion(Vec4(0.0f, 1.0f, 0.0f), 2.0f), Vec4(0.05f, 0.05f, 0.05f));

	const auto camera_transform = Transform(Vec4(0.0f, 20.0f, -30.0f), Quaternion(Vec4(1.0f, 0.0f, 0.0f), degrees_to_radians(40.0f)));
	auto camera = Camera(camera_transform, Mat4::perspective(degrees_to_radians(70.0f), static_cast<float>(window->width()) / static_cast<float>(window->height()), 0.1f, 1000.0f));

	renderer.set_light_direction(Vec4(0.0f, 0.0f, -1.0f));
	auto ambient_lighting_intensity = 0.1f;

	auto dt = 0.016f;
	Timer timer;
	timer.start();
	auto num_frames = 0;

	std::cout << "Mesh: " << mesh.filename() << " Num vertices: " << mesh.num_vertices() << std::endl;

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

		//ambient_lighting_intensity += 0.001;
		renderer.set_ambient_lighting_intensity(ambient_lighting_intensity);

		const auto vp = camera.view_projection();

		transform = transform.rotate(Quaternion(Vec4(0.0f, 1.0f, 0.0f), dt));

		renderer.draw_mesh(mesh, vp, transform.transformation(), texture);

		window->update();

		dt = (timer.get_ticks_since_last_call() / 1000.f);
		float avg_fps = num_frames / (timer.get_ticks() / 1000.f);
		if (avg_fps > 2000000)
		{
			// The first couple of frames the elapsed time count is tiny and will spike the fps.
			avg_fps = 0;
		}

		if (num_frames % 100 == 0)
		{
			std::cout << "dt: " << dt << " fps: " << avg_fps << "\r";
		}

		num_frames++;
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