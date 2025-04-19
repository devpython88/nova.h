#include "nova.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    NovaWindow win(800, 600, "game");
    NovaRenderDevice::framerateLimit(60);

    NovaRectangle r1(20, 20, 50, 50, YELLOW);
    NovaRectangle r2(400, 230, 30, 30, GREEN);
    NovaRectangle r3(100, 330, 30, 30, GREEN);
    NovaRectangle parent(140, 100, 50, 50, BLUE);
    
    NovaObjectChain chain(&parent);
    chain.addChild(&r1);

    NovaObjectChain chain2(&r2);
    chain2.addChild(&r3);

    chain.addSubChain(&chain2);

    while (win.open()){
        parent.x++;
        r2.x += 2;
        chain.rechain();

        // Obstacle
        
        win.start();
        NovaRenderDevice::fill(WHITE);
        NovaRenderDevice::rect(parent);
        NovaRenderDevice::rect(r1);
        NovaRenderDevice::rect(r2);
        NovaRenderDevice::rect(r3);

        win.end();
    }

    return 0;
}
