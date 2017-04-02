#include "renderer.h"

#include "window.h"

namespace kiwi {

	Renderer::Renderer(Window *window)
		:
		window_(window)
	{
	}

	void Renderer::clear(uint8_t r, uint8_t g, uint8_t b)
	{
		for (auto i = 0; i < window_->back_buffer_size_; i += 3)
		{
			window_->back_buffer_[i] = b;
			window_->back_buffer_[i + 1] = g;
			window_->back_buffer_[i + 2] = r;
		}
	}

}
