
<img src="/novaIcon.png" width="300"/>

### This library is actually really buggy so i switched to C and SDL2, You should check out core.2d (My new game library)

Nova.h is a simple library that is designed to user friendly and is built on top of raylib.

It aims to provide built-in features that other game development libraries don't tend to.

In nova, If you want a parent-child system, That's built-in, If you want a vehicle quickly, That's built-in and the same goes for caching, grouping, and much more.

Here is a example code written in nova.h:
```cpp
#include <nova.h>


int main(int argc, char const *argv[])
{
    NovaWindow window;
    NovaRenderDevice::framerateLimit(30);

    NovaRawTexture tx("some_anim.png");
    NovaAnimation anim(&tx, 200, 200, 16, 16); // (tx*, x, y, frameWidth, frameHeight)
    anim.setFramerate(16);
    anim.looping = true;
    NovaRectangle rectangle(20, 20, 50, 50, RED, 45); // Rotate by 45.(optional)
    NovaCircle circle(100, 100, 20, BLUE); // Circle

    while (window.open()){
        anim.play(); // Update frame
        window.start();
        
        NovaRenderDevice::fill(WHITE);
        anim.render();
        NovaRenderDevice::rect(rectangle);
        NovaRenderDevice::circle(circle);

        // example immediate mode rendering
        NovaRenderDevice::rect(50, 50, 20, 20, YELLOW);

        window.end();
    }

    tx.dispose();
    window.close();
    return 0;
}
```
Compilation:

If you have raylib and nova in global compiler directories: `g++ -o main main.cpp -lraylib -lnova`

If you do not: `g++ -o main main.cpp -Ipath/to/nova/include -Ipath/to/raylib/include -Lpath/to/nova/lib -Lpath/to/raylib/lib -lraylib -lnova`
