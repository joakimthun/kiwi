#include "win32_window.h"

#include "../kiwi_exception.h"

namespace kiwi {

	Win32Window::Win32Window(int32_t width, int32_t height)
		:
		width_(width),
		height_(height),
		display_buffer_(width, height, 3)
	{
		hinstance_ = GetModuleHandle(NULL);

		wcex_.cbSize = sizeof(WNDCLASSEX);
		wcex_.style = CS_HREDRAW | CS_VREDRAW;
		wcex_.lpfnWndProc = WindowProc;
		wcex_.cbClsExtra = 0;
		wcex_.cbWndExtra = 0;
		wcex_.hInstance = hinstance_;
		wcex_.hIcon = LoadIcon(hinstance_, MAKEINTRESOURCE(IDI_APPLICATION));
		wcex_.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex_.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex_.lpszMenuName = NULL;
		wcex_.lpszClassName = L"Kiwi";
		wcex_.hIconSm = LoadIcon(wcex_.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

		if (!RegisterClassEx(&wcex_))
		{
			throw KiwiException("Call to RegisterClassEx failed");
		}

		DWORD window_style = WS_OVERLAPPEDWINDOW;
		RECT client_rect = { 0, 0, width, height };
		if (!AdjustWindowRectEx(&client_rect, window_style, false, NULL))
		{
			throw KiwiException("Call to AdjustWindowRectEx failed");
		}

		hwnd_ = CreateWindow(
			L"Kiwi",
			L"Kiwi",
			window_style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			// width
			client_rect.right - client_rect.left,
			// height
			client_rect.bottom - client_rect.top,
			NULL,
			NULL,
			hinstance_,
			NULL
		);

		if (!hwnd_)
		{
			throw KiwiException("Could not create window, call to CreateWindow ");
		}

		// Set "this" as user data so we can grab it in WindowProc
		SetWindowLongPtr(hwnd_, GWLP_USERDATA, (LONG_PTR)this);

		// Setup the BITMAPINFOHEADER
		bitmap_info_.biSize = sizeof(bitmap_info_);
		bitmap_info_.biWidth = width;

		// negative sign == render top-down
		bitmap_info_.biHeight = -height; 
		bitmap_info_.biPlanes = 1;

		// Each 3-byte triplet in the bitmap array represents the relative intensities of blue, green, and red, respectively, for a pixel
		bitmap_info_.biBitCount = 8 * 3;
		bitmap_info_.biCompression = BI_RGB;
	}

	int32_t Win32Window::width() const
	{
		return width_;
	}

	int32_t Win32Window::height() const
	{
		return height_;
	}

	void Win32Window::open()
	{
		ShowWindow(hwnd_, SW_SHOW);
		UpdateWindow(hwnd_);
	}

	void Win32Window::update()
	{
		RedrawWindow(hwnd_, NULL, NULL, RDW_INVALIDATE);
	}

	Bitmap &Win32Window::display_buffer()
	{
		return display_buffer_;
	}

	LRESULT  Win32Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto window = (Win32Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		switch (message)
		{
		case WM_PAINT: {
			HDC dc = GetDC(hWnd);
			
			StretchDIBits(dc,
				0, 0, window->width_, window->height_,
				0, 0, window->width_, window->height_,
				window->display_buffer_.data(), (BITMAPINFO*)&window->bitmap_info_,
				DIB_RGB_COLORS, SRCCOPY);
			
			ReleaseDC(hWnd, dc);
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}
