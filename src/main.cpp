#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Game");

    nrd::framerateLimit(24);
    NovaNotifier::notify("Hello!");

    while (window.open()){
        window.start();
        nrd::fill(WHITE);
        NovaNotifier::show();
        window.end();
    }

    window.close();

    return 0;
}
