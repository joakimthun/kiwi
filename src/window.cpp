#include "window.h"

namespace kiwi {

	static 
	LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto myWnd = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}

		return 0;
	}

	Window::Window(int width, int height)
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
			MessageBox(NULL, L"Call to RegisterClassEx failed!", L"Kiwi", NULL);
			return;
		}

		DWORD window_style = WS_OVERLAPPEDWINDOW;
		RECT client_rect = { 0, 0, width, height };
		if (!AdjustWindowRectEx(&client_rect, window_style, false, NULL))
		{
			MessageBox(NULL, L"Call to AdjustWindowRectEx failed!", L"Kiwi", NULL);
			return;
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

		SetWindowLongPtr(hwnd_, GWLP_USERDATA, (LONG_PTR)this);
	}

	Window::~Window()
	{

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

}
