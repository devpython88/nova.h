#include <iostream>
#include "nova.h"
#include "novafile.h"
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaEvent event;
    NovaRectangle rec(20, 20, 40, 40, RED);

    while (window.open()){
        event.fetch();

        window.start();
        nrd::fill(WHITE); 
        nrd::rect(rec);
        window.end();
    }

    window.close();

    return 0;
}
