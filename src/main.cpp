#include "nova.h"


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    std::string text = "Hello!";

    while (window.open()){
        if (NovaInputDevice::getScrollEx() < 0){
            text = "Down!";
        }
        else if (NovaInputDevice::getScroll() > 0.0f){
            text = "Up!";
        }

        window.start();
        
        NovaRenderDevice::fill(WHITE);
        NovaRenderDevice::text(text, 20, 20, 18, RED);

        window.end();
    }
    return 0;
}
