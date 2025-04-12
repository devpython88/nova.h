#include "nova.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    NovaWindow win;

    NovaRectangle rect(20, 20, 40, 40, RED);
    NovaRectangle rect2(20, 20, 40, 40, RED);

    while (win.open()){
        if (NovaRenderDevice::checkCollision(rect, rect2));

        win.start();
        NovaRenderDevice::fill(WHITE);

        win.end();
    }
    return 0;
}
