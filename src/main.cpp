#include <iostream>

#include "glm\vec4.hpp"

#include "window.h"
#include "renderer.h"
#include "stars.h"
#include "vertex.h"

using namespace kiwi;

// TODO: Use a real timer...
const float dt = 0.0016f;

int main(int argc, char* argv[])
{
	glm::vec4 v4(0, 0, 0, 0);

	Window window(800, 600);
	window.open();

	Renderer renderer(&window);
	renderer.clear(0x00, 0x00, 0x00);

	//Stars stars(8000, 64.0f, 60.0f);

	Vertex min_y(100, 100);
	Vertex mid_y(150, 200);
	Vertex max_y(80, 300);

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

		//renderer.scan_convert_triangle(min_y, mid_y, max_y, 0);
		//renderer.fill_shape(100, 300);

		renderer.fill_triangle(mid_y, max_y, min_y);

		/*for (auto i = 100; i < 200; i++)
		{
			renderer.set_scan_buffer(i, 300 - i, 300 + i);
		}

		static int y_max = 100;

		renderer.fill_shape(100, y_max++);

		if (y_max >= 600)
			y_max = 100;*/


		//stars.frame(&renderer, dt);
		window.update();
	}

	return 0;
}