#include <Windows.h>
#include "Application.h"

// Main code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Application app;
    app.Run();
    return 0;
}