#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;


int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    nrd::framerateLimit(24);

    NovaRectangle rec(20, 20, 50, 50, RED);
    
    while (window.open()){
        window.start();
        nrd::fill(WHITE);
        nrd::rect(rec);
        window.end();
    }

    window.close();

    return 0;
}
