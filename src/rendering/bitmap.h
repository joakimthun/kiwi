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
		const uint8_t *data() const;
		uint64_t data_size() const;
		uint8_t stride() const;

		void clear(uint8_t r, uint8_t g, uint8_t b);
		void put_pixel(int32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
		void copy_pixel(int32_t dest_x, uint32_t dest_y, int32_t src_x, uint32_t src_y, const Bitmap& src);
		uint8_t get_component(std::size_t index) const;

	private:
		int32_t width_;
		int32_t height_;
		uint8_t *data_;
		uint64_t data_size_;
		const uint8_t stride_;
	};

}