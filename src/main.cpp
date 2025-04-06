#include "nova.h"


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    NovaAnimation sheet("glob.png", 20, 20, 32, 32);
    sheet.maxFrameTime = 3.0f;
    sheet.loop = true;

    sheet.row = 1;
    sheet.column = 1;

    NovaSound sound("test.wav");
    
    while (window.open()){
        sheet.play();

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
