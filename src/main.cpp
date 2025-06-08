#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Game");

    nrd::framerateLimit(60);

    
    NovaRectangle rec(200, 200, 50, 50, RED);
    NovaRawTexture tx("glob.png");

    NovaSpritesheet im(&tx, 400, 400, 32, 64);
    im.flipY = true;

    while (window.open()){
        window.start();
        nrd::fill(BLUE);
        nrd::rect(rec);
        im.render();
        window.end();
    }

    tx.dispose();
    window.close();

    return 0;
}
