#include <iostream>

#include "window.h"

using namespace kiwi;

int main(int argc, char* argv[])
{
	Window window(800, 600);
	window.open();

	MSG msg;
	while (true)
	{
		while(window.peek_message(&msg)) {}
	}

	return 0;
}