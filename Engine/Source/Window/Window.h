#pragma once
#include <Windows.h>
#include <stdexcept>

class Window
{
public:
    Window(WNDCLASSEXW wc);
    ~Window();

    HWND GetHandle() const { return WindowHWND; }
    void Show() const;

private:
    WNDCLASSEXW WindowWC;
    HWND WindowHWND;
};