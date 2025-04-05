#include "nova.h"


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    NovaSpritesheet sheet("glob.png", 20, 20, 32, 32);
    sheet.row = 1;
    sheet.column = 1;
    
    while (window.open()){
        if (NovaInputDevice::keyHit(KEY_A)){
            sheet.column++;
        }

        window.start();
        
        NovaRenderDevice::fill(WHITE);
    
        sheet.render();

        window.end();
    }
    return 0;
}
