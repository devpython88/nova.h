#include "nova.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    NovaInputManager manager;
    manager.bindKey("Hello", KEY_A);
    manager.bindMouse("Hello v2.0", MOUSE_BUTTON_LEFT);

    while (window.open()){

        if (manager.held("Hello")) std::cout << "Hello\n";
        if (manager.hit("Hello v2.0")) std::cout << "Hello v2.0\n";
        

        window.start();
        
        NovaRenderDevice::fill(WHITE);

        window.end();
    }
    return 0;
}
