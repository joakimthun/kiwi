#include "sdl_window.h"

#include <cstring>

#include "kiwi_exception.h"

namespace kiwi {

	SDLWindow::SDLWindow(int32_t width, int32_t height)
		:
		width_(width),
		height_(height),
		display_buffer_(width, height, 4)
	{
		sdl_window_ = SDL_CreateWindow("Kiwi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
		if(!sdl_window_)
			throw KiwiException("Could not create sdl window: " + std::string(SDL_GetError()));

		sdl_window_surface_ = SDL_GetWindowSurface(sdl_window_);
		if (!sdl_window_surface_)
			throw KiwiException("Could not create sdl window surface: " + std::string(SDL_GetError()));
	}

	SDLWindow::~SDLWindow()
	{
		SDL_DestroyWindow(sdl_window_);
	}

	int32_t SDLWindow::width() const
	{
		return width_;
	}

	int32_t SDLWindow::height() const
	{
		return height_;
	}

	void SDLWindow::open()
	{
		SDL_ShowWindow(sdl_window_);
	}

	void SDLWindow::update()
	{
		SDL_LockSurface(sdl_window_surface_);

		std::memcpy(sdl_window_surface_->pixels, display_buffer_.data(), display_buffer_.data_size());

		SDL_UnlockSurface(sdl_window_surface_);

		SDL_UpdateWindowSurface(sdl_window_);
	}

	Bitmap &SDLWindow::display_buffer()
	{
		return display_buffer_;
	}

}
