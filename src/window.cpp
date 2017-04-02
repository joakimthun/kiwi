#include "window.h"

#include "kiwi_exception.h"

namespace kiwi {

	Window::Window(int32_t width, int32_t height)
		:
		width_(width),
		height_(height)
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

		// Setup back buffer and the BITMAPINFOHEADER
		back_buffer_size_ = width * height * 3;
		back_buffer_ = (uint8_t*)calloc(back_buffer_size_, 1);

		bitmap_info_.biSize = sizeof(bitmap_info_);
		bitmap_info_.biWidth = width;

		// negative sign == render top-down
		bitmap_info_.biHeight = -height; 
		bitmap_info_.biPlanes = 1;

		// Each 3-byte triplet in the bitmap array represents the relative intensities of blue, green, and red, respectively, for a pixel
		bitmap_info_.biBitCount = 8 * 3;
		bitmap_info_.biCompression = BI_RGB;
	}

	Window::~Window()
	{
		if (back_buffer_)
		{
			free(back_buffer_);
			back_buffer_ = nullptr;
		}
	}

	void Window::open()
	{
		ShowWindow(hwnd_, SW_SHOW);
		UpdateWindow(hwnd_);
	}

	bool Window::peek_message(MSG *msg)
	{
		if (PeekMessage(msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(msg);
			DispatchMessage(msg);
			return true;
		}

		return false;
	}

	LRESULT  Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		switch (message)
		{
		case WM_PAINT: {
			HDC dc = GetDC(hWnd);
			
			StretchDIBits(dc,
				0, 0, window->width_, window->height_,
				0, 0, window->width_, window->height_,
				window->back_buffer_, (BITMAPINFO*)&window->bitmap_info_,
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}

		return 0;
	}

}
