#include "nova.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    NovaWindow win;
    NovaRenderDevice::framerateLimit(60);

    while (win.open()){
        // Obstacle
        
        win.start();
        NovaRenderDevice::fill(WHITE);

        win.end();
    }

    return 0;
}
