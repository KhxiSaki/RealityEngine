#include <iostream>
#include <engine/window/window.h>



int main(int args, char* argv[])
{
    real::window_desc desc{};
    desc.cx = 1024;
    desc.cy = 780;
    desc.title = "reality engine";
    real::window* window = new real::window(&desc);


    
    return 0;
}