#include "Window.h"
#include <string>

Window::Window(WNDCLASSEXW wc) : WindowWC(wc), WindowHWND(nullptr)
{
    // Register the window class
    if (!RegisterClassExW(&WindowWC)) {

        throw std::runtime_error("Failed to register window class: " + std::to_string(GetLastError()));

    }

    // Create the window
    WindowHWND = CreateWindowW(WindowWC.lpszClassName, L"RealityEngine", WS_OVERLAPPEDWINDOW,
        100, 100, 1920, 1080, nullptr, nullptr, WindowWC.hInstance, nullptr);

    if (WindowHWND == nullptr)
    {
        throw std::runtime_error("Failed to create window:" + std::to_string(GetLastError()));
    }
}

Window::~Window()
{
    if (WindowHWND)
    {
        DestroyWindow(WindowHWND);
    }
    UnregisterClassW(WindowWC.lpszClassName, WindowWC.hInstance);
}

void Window::Show() const
{
    ShowWindow(WindowHWND, SW_SHOWDEFAULT);
    UpdateWindow(WindowHWND);
}