#include <windows.h>
#include <stdexcept>
#include "../../Engine/Source/Window.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window window(hInstance, L"RealityEngineClass", L"RealityEngine");
		window.Show(nCmdShow);
		window.Run();
	}
	catch (const std::runtime_error& e)
	{
		MessageBoxW(NULL, L"Error: Failed to create window", L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	return 0;
}