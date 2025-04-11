#include "nova.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    NovaInputManager manager;
    manager.bindKey("Hello", KEY_A);
    manager.bindMouse("Hello v2.0", MOUSE_BUTTON_LEFT);

    NovaAxis axis = window.axis();

    while (window.open()){

        window.start();
        
        NovaRenderDevice::fill(WHITE);

        window.end();
    }
    return 0;
}
