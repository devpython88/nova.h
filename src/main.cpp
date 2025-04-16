#include "nova.h"
#include <iostream>
#include "novafile.h"

int main(int argc, char const *argv[])
{
    NovaWindow win;
    NovaRenderDevice::framerateLimit(60);

    NovaFS::mkdir("unix");
    NovaFS::mkdir("unix/win");
    NovaFS::Win32FS::move("unix", "dist-msys");

    while (win.open()){
        // Obstacle
        
        win.start();
        NovaRenderDevice::fill(WHITE);

        NovaRenderDevice::poly(400, 300, 3, 20, RED);

        win.end();
    }

    return 0;
}
