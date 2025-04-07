#include "nova.h"


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    NovaMusic music("test.mp3");
    music.play();

    while (window.open()){
        music.update();
        
        window.start();
        
        NovaRenderDevice::fill(WHITE);
        NovaRenderDevice::text("Hello!", 20, 20, 18, RED);

        window.end();
    }
    return 0;
}
