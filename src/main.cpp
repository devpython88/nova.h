
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
    NovaRectangle rec1(100, 80, 50, 50, RED);
    NovaRectangle rec2(100, 140, 50, 50, BLUE);
    NovaRectangle rec3(100, 200, 50, 50, GREEN);
    NovaRectangle rec4(100, 260, 50, 50, YELLOW);
    NovaRectangle rec5(100, 320, 50, 50, PINK);
    NovaRectangle rec6(100, 380, 50, 50, ORANGE);

    NovaTagDevice::addObject("zombie", &rec1);
    NovaTagDevice::addObject("zombie", &rec2);
    NovaTagDevice::addObject("zombie", &rec3);

    NovaTagDevice::getFirst("zombie"); // returns first tagged, nullptr if not found
    NovaTagDevice::getAll("zombie"); // returns all tagged
    NovaTagDevice::getMax("zombie", 2); // returns all tagged but maxed on `count`

    // NovaTagDevice::removeFirst("zombie");
    // NovaTagDevice::removeAll("zombie");
    // NovaTagDevice::removeMax("zombie", 2);

    NovaCamera cam;

    while (window.open()){
        event.fetch(); // get event
        rec1.updateMovement(); 
        NovaScheduler::update();
        
        window.start();
        cam.start();

        nrd::fill(BLUE);

        nrd::rect(rec1);
        nrd::rect(rec2);
        nrd::rect(rec3);
        nrd::rect(rec4);
        nrd::rect(rec5);
        nrd::rect(rec6);

        cam.end();
        window.end();
    }

    window.close();

    return 0;
}
