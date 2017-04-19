#pragma once

#include "rendering/bitmap.h"

namespace kiwi {

	class Window
	{
	public:
		inline ~Window() {}

		virtual int32_t width() const = 0;
		virtual int32_t height() const = 0;
		virtual void open() = 0;
		virtual void update() = 0;
		virtual Bitmap &display_buffer() = 0;
	};

}