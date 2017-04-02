#include <iostream>

#include "window.h"
#include "renderer.h"

using namespace kiwi;

int main(int argc, char* argv[])
{
	Window window(800, 600);
	window.open();

	Renderer renderer(&window);
	renderer.clear(0, 0, 255);

	renderer.set_pixel(10, 10, 255, 0, 0);
	renderer.set_pixel(10, 11, 255, 0, 0);
	renderer.set_pixel(10, 11, 255, 0, 0);
	renderer.set_pixel(10, 12, 255, 0, 0);
	renderer.set_pixel(10, 13, 255, 0, 0);
	renderer.set_pixel(10, 14, 255, 0, 0);

	renderer.set_pixel(11, 10, 255, 0, 0);
	renderer.set_pixel(11, 11, 255, 0, 0);
	renderer.set_pixel(11, 11, 255, 0, 0);
	renderer.set_pixel(11, 12, 255, 0, 0);
	renderer.set_pixel(11, 13, 255, 0, 0);
	renderer.set_pixel(11, 14, 255, 0, 0);

	renderer.set_pixel(10, 10, 255, 0, 0);
	renderer.set_pixel(10, 11, 255, 0, 0);
	renderer.set_pixel(10, 11, 255, 0, 0);
	renderer.set_pixel(10, 12, 255, 0, 0);
	renderer.set_pixel(10, 13, 255, 0, 0);
	renderer.set_pixel(10, 14, 255, 0, 0);

	MSG msg;
	while (true)
	{
		while(window.peek_message(&msg)) {}
	}

	return 0;
}