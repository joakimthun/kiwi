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

	MSG msg;
	while (true)
	{
		while(window.peek_message(&msg)) {}
	}

	return 0;
}