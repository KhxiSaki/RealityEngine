#include "window.h"
#include "window_config.h"

namespace real
{
    window::window(const window_desc* desc)
    {
        WNDCLASSEXA wc{};
        wc.cbSize = sizeof(wc);
        wc.hInstance = GetModuleHandleA(nullptr);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.lpszClassName = "engine++";
        wc.lpfnWndProc = window::global_proc;
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(DKGRAY_BRUSH));
        
        ATOM res = RegisterClassExA(&wc);
        if(FAILED(res)){
            ExitProcess(-1);
        }

        int x = (GetSystemMetrics(SM_CXSCREEN) - desc->cx) / 2;
        int y = (GetSystemMetrics(SM_CYSCREEN) - desc->cy) / 2;

        m_hwnd = CreateWindowExA(0,
        wc.lpszClassName,
        desc->title,
        WS_OVERLAPPEDWINDOW,
        x,y,desc->cx, desc->cy, nullptr,
        0, wc.hInstance, nullptr
        );

        ::ShowWindow(m_hwnd, SW_SHOW);

    }

    LRESULT window::global_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        return DefWindowProcA(hwnd, msg, wp, lp);
    }

    int window::exec(void *scene)
    {
        MSG msg{};

        while (msg.message != WM_QUIT)
        {
            while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
            
        }
        

        return (int)msg.lParam;
    }

} // namespace real
