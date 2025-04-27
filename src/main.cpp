#include <iostream>
#include "nova.h"
#include "novafile.h"
#include <sstream>

using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaLogger::info("yaya");

    while (window.open()){

        window.start();
        nrd::fill(WHITE);
        window.end();
    }

    return 0;
}
