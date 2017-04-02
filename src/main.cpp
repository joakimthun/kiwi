#include <iostream>

#include "window.h"
#include "renderer.h"
#include "stars.h"

using namespace kiwi;

// TODO: Use a real timer...
const float dt = 0.0016;

int main(int argc, char* argv[])
{
	Window window(800, 600);
	window.open();

	Renderer renderer(&window);
	renderer.clear(0, 0, 0);

	Stars stars(8000, 64.0f, 30.0f);

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

		stars.frame(&renderer, dt);
		window.update();
	}

	return 0;
}