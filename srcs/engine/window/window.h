#pragma once

#include <engine/core/typedef.h>

namespace real
{
    class window
    {
    public:
        window(const window_desc* desc);

        static LRESULT WINAPI global_proc(HWND, UINT, WPARAM, LPARAM);
        static int exec(void* scene);

        HWND m_hwnd;
        //HGLRC m_rc;   TODO : to context
        //HDC m_dc;     TODO : to swapchain
    };
} // namespace reality
