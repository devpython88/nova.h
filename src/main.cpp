#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Game");

    nrd::framerateLimit(60);

    NovaRawTexture texture("glob.png");
    NovaAnimation anim(&texture, 200, 200, 16, 16);
    anim.setFramerate(2);
    anim.loop = true;
    anim.velocity = NovaVec2(20, 20);

    NovaVehicle veh(
        &anim,
        NovaVehicleConfig(100.0f, 0.2f, 0.2f, .2f, 5.0f),
        KEY_W, KEY_S, KEY_A, KEY_D
    );

    while (window.open()){
        anim.play();
        veh.drive();
        window.start();
        nrd::fill(WHITE);
        anim.render();
        window.end();
    }

    texture.dispose();
    window.close();

    return 0;
}
