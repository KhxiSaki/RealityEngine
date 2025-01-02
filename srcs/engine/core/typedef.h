#pragma once

#include <cstdint>
// stardard integers
typedef uint8_t     uint8, byte;
typedef uint16_t    uint16;
typedef uint32_t    uint32, uint;
typedef uint64_t    uint64;


namespace real
{
    struct window_desc
    {
        uint cx;
        uint cy;
        const char* title;
    };
    
} // namespace real
