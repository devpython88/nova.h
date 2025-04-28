#include <iostream>
#include "nova.h"
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    while (window.open()){
        window.start();
        nrd::fill(WHITE); 
        window.end();
    }

    return 0;
}
