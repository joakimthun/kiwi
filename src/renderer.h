#pragma once

#include <stdint.h>

namespace kiwi {

	class Window;

	class Renderer
	{
	public:
		Renderer(Window *window);

		void clear(uint8_t r, uint8_t g, uint8_t b);
	private:
		Window *window_;
	};

}