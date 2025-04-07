#include "nova.h"


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    while (window.open()){
        
        window.start();
        
        NovaRenderDevice::fill(WHITE);
        
        window.end();
    }
    return 0;
}
