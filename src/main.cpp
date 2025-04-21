#include "nova.h"
#include "novastr.h"
int main(int argc, char const *argv[])
{
    NovaWindow win(800, 600, "game");
    NovaRenderDevice::framerateLimit(30);

    NovaTypeWriter writer("Hello world!", 0.1f);

    while (win.open()){
        if (writer.getCurrentText() == "Hell"){
            writer.pause();
        }
        writer.update();
        
        win.start();
        NovaRenderDevice::fill(WHITE);
        NovaRenderDevice::text(writer.getCurrentText(), 20, 20, 32, RED);

        win.end();
    }

    return 0;
}
