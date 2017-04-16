#pragma once

#include "rendering/bitmap.h"

namespace kiwi {

	class Window
	{
	public:
		inline ~Window() {}

		virtual void open() = 0;
		virtual void update() = 0;
		virtual Bitmap &display_buffer() = 0;
	};

}