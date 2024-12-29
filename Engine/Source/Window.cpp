#include "Window.h"

Window::Window(HINSTANCE hInstance, const wchar_t* className, const wchar_t* windowTitle)
	: hInstance(hInstance), className(className), windowTitle(windowTitle), hwnd(NULL)
{
	RegisterClass();
	Create();
}

Window::~Window()
{
	hInstance = nullptr;
	className = nullptr;
	windowTitle = nullptr;
	hwnd = nullptr;
}

void Window::RegisterClass()
{
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	// Register the window class
	if (!::RegisterClass(&wc))
	{
		throw std::runtime_error("Failed to register window class");
	}
}

void Window::Create()
{
	hwnd = CreateWindowEx(
		0,
		className,
		windowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		throw std::runtime_error("Failed to create window");
	}
}

void Window::Show(int nCmdShow)
{
	::ShowWindow(hwnd, nCmdShow);
}

void Window::Run()
{
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}