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
		scan_buffer_.resize(height_ * 2);
	}

	int32_t Renderer::width()
	{
		return width_;
	}

	int32_t Renderer::height()
	{
		return height_;
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

	void Renderer::put_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
	{
		int index = (x + y * width_) * 3;
		back_buffer_[index] = b;
		back_buffer_[index + 1] = g;
		back_buffer_[index + 2] = r;
	}

	void Renderer::set_scan_buffer(uint32_t y, uint32_t x_min, uint32_t x_max)
	{
		scan_buffer_[y * 2] = x_min;
		scan_buffer_[y * 2 + 1] = x_max;
	}

	void Renderer::fill_shape(uint32_t y_min, uint32_t y_max)
	{
		for (auto i = y_min; i < y_max; i++)
		{
			const auto x_min = scan_buffer_[i * 2];
			const auto x_max = scan_buffer_[i * 2 + 1];

			for (auto j = x_min; j < x_max; j++)
			{
				put_pixel(j, i, 0xFF, 0xFF, 0xFF);
			}
		}
	}

}
