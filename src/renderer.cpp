#include "renderer.h"

#include "window.h"

namespace kiwi {

	Renderer::Renderer(Window *window)
		:
		window_(window),
		width_(window->width_),
		height_(window->height_),
		back_buffer_(window->back_buffer_),
		back_buffer_size_(window->back_buffer_size_)
	{
	}

	void Renderer::clear(uint8_t r, uint8_t g, uint8_t b)
	{
		for (auto i = 0; i < back_buffer_size_; i += 3)
		{
			back_buffer_[i] = b;
			back_buffer_[i + 1] = g;
			back_buffer_[i + 2] = r;
		}
	}

	void Renderer::set_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
	{
		int index = (x + y * width_) * 3;
		back_buffer_[index] = b;
		back_buffer_[index + 1] = g;
		back_buffer_[index + 2] = r;
	}

}
