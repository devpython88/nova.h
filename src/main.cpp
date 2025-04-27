#include <iostream>
#include "nova.h"
#include "novafile.h"
#include <sstream>

using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaSignal signal;
    signal.callback = SIGNAL([&]() {
        NovaLogger::info("function");
    });

    NovaEvent event;

    while (window.open()){
        event.fetch();
        if (event.lastKeyHit == NovaEvent::Key::A){
            signal.emit();
        }

        window.start();
        nrd::fill(WHITE);
        window.end();
    }

    return 0;
}
