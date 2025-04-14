#include "nova.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    NovaWindow win;
    NovaRenderDevice::framerateLimit(60);

    NovaModal modal("Hello", 20, 20);

    while (win.open()){
        // Obstacle
        
        win.start();
        NovaRenderDevice::fill(WHITE);

        modal.draw();

        win.end();
    }

    return 0;
}
