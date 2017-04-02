#pragma once

#include <stdint.h>

namespace kiwi {

	class Window;

	class Renderer
	{
	public:
		Renderer(Window *window);


		int32_t width();
		int32_t height();
		void clear(uint8_t r, uint8_t g, uint8_t b);
		void put_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
	private:
		Window *window_;
		int32_t width_;
		int32_t height_;
		uint8_t *back_buffer_;
		const uint64_t back_buffer_size_;
	};

}