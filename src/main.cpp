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
    
    while (window.open()){
        window.start();
        nrd::fill(WHITE);
        nrd::rect(rec);
        window.end();
    }

    window.close();

    return 0;
}
