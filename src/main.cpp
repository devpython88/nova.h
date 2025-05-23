#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;


int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    nrd::framerateLimit(60);
    while (window.open()){

        window.start();
        nrd::fill(WHITE);
        window.end();
    }

    window.close();

    return 0;
}
