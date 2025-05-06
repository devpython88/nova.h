#include <iostream>
#include "nova.h"
#include "novafile.h"
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaEvent event;
    
    NovaLogFile file("client", "log");

    file.info("this is info");
    file.warning("This is awanring");
    file.error("err");
    file.fatal("fata");
    file.info("informason");
    file.close();

    while (window.open()){
        event.fetch();

        window.start();
        nrd::fill(WHITE);
        window.end();
    }

    window.close();

    return 0;
}
