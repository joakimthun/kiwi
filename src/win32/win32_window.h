#pragma once

#include <Windows.h>
#include <stdint.h>

#include "../window.h"

namespace kiwi {

	class Win32Window : public Window
	{
	public:
		Win32Window(int32_t width, int32_t height);

		void open();
		void update();
		Bitmap &display_buffer();

	private:
		static LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		int32_t width_;
		int32_t height_;
		Bitmap display_buffer_;
		WNDCLASSEX wcex_;
		HINSTANCE hinstance_;
		HWND hwnd_;
		BITMAPINFOHEADER bitmap_info_ = { 0 };
	};

}