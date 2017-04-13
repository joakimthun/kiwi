#pragma once

#include <stdint.h>
#include <cstddef>

namespace kiwi {

	class Bitmap
	{
	public:
		Bitmap(int32_t width, int32_t height);
		~Bitmap();

		int32_t width() const;
		int32_t height() const;
		void put_pixel(int32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
		uint8_t get_component(std::size_t index) const;

	private:
		int32_t width_;
		int32_t height_;
		uint8_t *data_;
		uint64_t data_size_;
	};

}