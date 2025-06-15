
#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include "novatime.h"

#include <thread>
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Button Smasher");
    window.integratedCamera = false;

    nrd::framerateLimit(60);

    NovaEvent event; // to keep event
    NovaRectangle rec(80, 80, 50, 50, RED);

    NovaCamera cam;
    cam.shaking = true;
    cam.setShakePower(5.0f);

    NovaScheduler::addTask("whatever", 3.5f, [&](){
        cam.shaking = false;
    });

    while (window.open()){
        event.fetch(); // get event
        rec.updateMovement(); 
        NovaScheduler::update();

        window.start();
        cam.start();

        nrd::fill(BLUE);
        nrd::rect(rec);

        cam.end();
        window.end();
    }

    window.close();

    return 0;
}
