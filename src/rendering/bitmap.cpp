#include "bitmap.h"

#include <stdlib.h>

namespace kiwi {

	Bitmap::Bitmap(int32_t width, int32_t height)
		:
		width_(width),
		height_(height),
		stride_(3)
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

	const uint8_t *Bitmap::data() const
	{
		return data_;
	}

	uint64_t Bitmap::data_size() const
	{
		return data_size_;
	}

	uint8_t Bitmap::stride() const
	{
		return stride_;
	}

	void Bitmap::clear(uint8_t r, uint8_t g, uint8_t b)
	{
		for (auto i = 0; i < data_size_; i += stride_)
		{
			data_[i] = b;
			data_[i + 1] = g;
			data_[i + 2] = r;
		}
	}

	void Bitmap::put_pixel(int32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
	{
		int index = (x + y * width_) * stride_;
		data_[index] = b;
		data_[index + 1] = g;
		data_[index + 2] = r;
	}

	void Bitmap::copy_pixel(int32_t dest_x, uint32_t dest_y, int32_t src_x, uint32_t src_y, const Bitmap& src, float light_factor)
	{
		const auto dest_index = (dest_x + dest_y * width_) * stride_;
		const auto src_index = (src_x + src_y * src.width_) * stride_;

		data_[dest_index] = src.get_component(src_index, light_factor);
		data_[dest_index + 1] = src.get_component(src_index + 1, light_factor);
		data_[dest_index + 2] = src.get_component(src_index + 2, light_factor);
	}

	uint8_t Bitmap::get_component(std::size_t index) const
	{
		return data_[index];
	}

	uint8_t Bitmap::get_component(std::size_t index, float light_factor) const
	{
		return static_cast<uint8_t>(data_[index] * light_factor);
	}

}
