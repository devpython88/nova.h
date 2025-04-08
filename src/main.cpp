#include "nova.h"


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    std::string text = "Hello!";

    while (window.open()){
        if (NovaInputDevice::keyHeld(KEY_A)){
            window.target()->x--;
        }

        if (NovaInputDevice::keyHeld(KEY_D)){
            window.target()->x++;
        }


        if (NovaInputDevice::mouseButtonHit(MOUSE_BUTTON_LEFT)){
            window.centerCamera(20, 20);
        }
        

        window.start();
        
        NovaRenderDevice::fill(WHITE);
        NovaRenderDevice::text(text, 20, 20, 18, RED);

        window.end();
    }
    return 0;
}
