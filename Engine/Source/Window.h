#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdexcept>

class Window
{
public:
	Window(HINSTANCE hInstance, const wchar_t* className, const wchar_t* windowTitle);
	~Window();
	void Show(int nCmdShow);
	void Run();

private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void RegisterClass();
	void Create();

	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className;
	const wchar_t* windowTitle;
};
