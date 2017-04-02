#pragma once

#include <Windows.h>

namespace kiwi {

	class Window
	{
	public:
		Window(int width, int height);
		~Window();

		void open();
		bool peek_message(MSG *msg);
	private:
		WNDCLASSEX wcex_;
		HINSTANCE hinstance_;
		HWND hwnd_;
	};

}