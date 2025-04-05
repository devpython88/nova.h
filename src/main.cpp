#include "nova.h"


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    NovaRenderImage image(300, 200, "glob.png");
    NovaRectangle rectangle(20, 20, 50, 50, RED, 45); // Rotate by 45.(optional)
    NovaCircle circle(100, 100, 20, BLUE); // Circle

    while (window.open()){
        window.start();
        
        NovaRenderDevice::fill(WHITE);
        NovaRenderDevice::image(image);
        NovaRenderDevice::rect(rectangle);
        NovaRenderDevice::circle(circle);

        // example immediate mode rendering
        NovaRenderDevice::rect(50, 50, 20, 20, YELLOW);

        window.end();
    }
    return 0;
}
