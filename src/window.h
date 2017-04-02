#pragma once

#include <Windows.h>
#include <stdint.h>

namespace kiwi {

	class Renderer;

	class Window
	{
		friend class Renderer;
	public:
		Window(int32_t width, int32_t height);
		~Window();

		void open();
		void update();
	private:
		static LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		int32_t width_;
		int32_t height_;
		WNDCLASSEX wcex_;
		HINSTANCE hinstance_;
		HWND hwnd_;
		uint8_t *back_buffer_;
		uint64_t back_buffer_size_;
		BITMAPINFOHEADER bitmap_info_ = { 0 };
	};

}