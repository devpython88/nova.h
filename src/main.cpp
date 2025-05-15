#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;


int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaEvent event;
    nrd::framerateLimit(60);

    NovaRectangle rec(5, 5, 25, 25, RED);
    NovaFueledVehicle veh(&rec,
        NovaVehicleConfig(10.0f, 0.1f, 0.1f, 3.0f, 2.0f),
        NovaFuelConfig(20, 1),
        NovaEvent::Key::W,
        NovaEvent::Key::S,
        NovaEvent::Key::A,
        NovaEvent::Key::D
    );

    while (window.open()){
        veh.drive();

        window.start();
        nrd::fill(WHITE);
        nrd::rect(rec);
        nrd::text(std::to_string(veh.getValidSpeed()), 100, 100, 22, BLACK);
        nrd::text(std::to_string(veh.fuel), 100, 150, 22, BLACK);
        window.end();
    }

    window.close();

    return 0;
}
