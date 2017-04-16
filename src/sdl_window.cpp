#include "sdl_window.h"

#include "kiwi_exception.h"

namespace kiwi {

	SDLWindow::SDLWindow(int32_t width, int32_t height)
		:
		width_(width),
		height_(height),
		display_buffer_(width, height)
	{
		SDL_Init(SDL_INIT_VIDEO);

		sdl_window_ = SDL_CreateWindow("Kiwi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
		if(!sdl_window_)
			throw KiwiException("Could not create sdl window: ");

		sdl_window_surface_ = SDL_GetWindowSurface(sdl_window_);
		if (!sdl_window_surface_)
			throw KiwiException("Could not create sdl window surface");
	}

	SDLWindow::~SDLWindow()
	{
		SDL_DestroyWindow(sdl_window_);
	}

	void SDLWindow::open()
	{
		SDL_ShowWindow(sdl_window_);
	}

	void SDLWindow::update()
	{
		const auto display_buffer_data = display_buffer_.data();
		uint8_t *pixel = static_cast<uint8_t*>(sdl_window_surface_->pixels);

		SDL_LockSurface(sdl_window_surface_);

		for (auto x = 0; x < width_; x++)
		{
			for (auto y = 0; y < height_; y++)
			{
				const auto display_buffer_index = (x + y * display_buffer_.width()) * display_buffer_.stride();
				auto current_pixel = pixel + (y * sdl_window_surface_->pitch) + (x * sizeof(uint32_t));

				*((uint32_t*)current_pixel) = SDL_MapRGBA(
					sdl_window_surface_->format, 
					display_buffer_data[display_buffer_index], 
					display_buffer_data[display_buffer_index + 1], 
					display_buffer_data[display_buffer_index + 2], 
					0xFF);
			}
		}

		SDL_UnlockSurface(sdl_window_surface_);

		SDL_UpdateWindowSurface(sdl_window_);
	}

	Bitmap &SDLWindow::display_buffer()
	{
		return display_buffer_;
	}

}
