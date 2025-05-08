#include <iostream>
#include "nova.h"
#include <thread>
using nrd = NovaRenderDevice;


int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaEvent event;
    NovaRandomDevice rd;

    NovaRectangle rec(20, 20, 50, 50, RED);
    float cellX = 10.0f;
    float cellY = 10.0f;

    while (window.open()){
        event.fetch();

        cellX += event.mouseScroll.x;
        cellY += event.mouseScroll.y;

        window.start();
        nrd::fill(WHITE);
        nrd::gridBoxes(NovaVec2(20, 20), NovaVec2((int) cellX, (int) cellY), WHITE, GRAY);

        window.end();
    }

    window.close();

    return 0;
}
