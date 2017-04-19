#pragma once

#include <SDL.h>
#include <stdint.h>

#include "window.h"

namespace kiwi {

	class SDLWindow : public Window
	{
	public:
		SDLWindow(int32_t width, int32_t height);
		~SDLWindow();

		int32_t width() const override;
		int32_t height() const override;

		void open() override;
		void update() override;
		Bitmap &display_buffer() override;

	private:
		SDL_Window *sdl_window_;
		SDL_Surface *sdl_window_surface_;
		int32_t width_;
		int32_t height_;
		Bitmap display_buffer_;
	};

}