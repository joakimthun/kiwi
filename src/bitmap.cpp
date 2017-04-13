#include "bitmap.h"

#include <stdlib.h>

namespace kiwi {

	Bitmap::Bitmap(int32_t width, int32_t height)
		:
		width_(width),
		height_(height)
	{
		data_size_ = width * height * 3;
		data_ = (uint8_t*)calloc(data_size_, 1);
	}

	Bitmap::~Bitmap()
	{
		if (data_)
		{
			free(data_);
			data_ = nullptr;
		}
	}

	int32_t Bitmap::width() const
	{
		return width_;
	}

	int32_t Bitmap::height() const
	{
		return height_;
	}

	void Bitmap::put_pixel(int32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
	{
		int index = (x + y * width_) * 3;
		data_[index] = b;
		data_[index + 1] = g;
		data_[index + 2] = r;
	}

	uint8_t Bitmap::get_component(std::size_t index) const
	{
		return data_[index];
	}

}
