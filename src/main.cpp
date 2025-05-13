#include <iostream>
#include "nova.h"
#include "novastr.h"
#include <thread>
using nrd = NovaRenderDevice;


int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaEvent event;

    NovaMenu menu("File", NovaVec2(20, 20), 20);
    menu.addOption("Save");
    menu.addOption("Open");
    menu.addOption("New");

    while (window.open()){
        window.start();
        nrd::fill(WHITE);
        auto res = menu.show();

        if (res.clicked){
            NovaLogger::info(res.option);
        }
        window.end();
    }

    window.close();

    return 0;
}
