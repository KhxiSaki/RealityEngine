#pragma once

#include <cstdint>
// stardard integers
typedef uint8_t     uint8, byte;
typedef uint16_t    uint16;
typedef uint32_t    uint32, uint;
typedef uint64_t    uint64;

// ------- window api decl ---------
#define CALLBACK		__stdcall
#define WINAPI			__stdcall
#define APIENTRY		WINAPI

typedef unsigned int		UINT;
typedef unsigned long		DWORD;
typedef int					BOOL;
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef float				FLOAT;
typedef void* LPVOID;
typedef const char* LPCSTR;
typedef char* LPSTR;

#if defined(_WIN64)
#ifdef _MSC_VER
typedef __int64				INT_PTR;
typedef unsigned __int64	UINT_PTR;
typedef __int64				LONG_PTR;
typedef unsigned __int64	ULONG_PTR;
#else	//if gcc clang
typedef long long			INT_PTR;
typedef unsigned long long	UINT_PTR;
typedef long long			LONG_PTR;
typedef unsigned long long	ULONG_PTR;
#endif
#else	//if 32bit
typedef int					INT_PTR;
typedef unsigned int		UINT_PTR;
typedef long				LONG_PTR;
typedef unsigned long		ULONG_PTR;
#endif

typedef UINT_PTR		WPARAM;
typedef LONG_PTR		LPARAM;
typedef LONG_PTR		LRESULT;
typedef long			HRESULT;

struct	HWND__;
typedef HWND__  *HWND;
struct  HDC__;
typedef HDC__   *HDC;
struct  HGLRC__;
typedef HGLRC__ *HGLRC;


namespace real
{
    struct window_desc
    {
        uint cx;
        uint cy;
        const char* title;
    };
    
} // namespace real
