#include <iostream>
#include "nova.h"

using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaAnimation sheet("glob.png", 100, 100, 32, 32);
    sheet.setMaxFrameTime(2.0f);
    sheet.loop = true;

    while (window.open()){
        sheet.play();

        window.start();
        nrd::fill(WHITE);
        sheet.render();

        window.end();
    }

    sheet.dispose();

    return 0;
}
