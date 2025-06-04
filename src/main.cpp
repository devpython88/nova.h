#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;


int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Game");

    nrd::framerateLimit(24);

    std::vector<NovaJSON> stuff;

    for (int i = 0; i < 20; i++){
        NovaJSON j;
        j.set<int>("x", GetRandomValue(20, 60));
        j.set<int>("y", GetRandomValue(20, 60));
        j.set<int>("w", GetRandomValue(20, 60));
        j.set<int>("h", GetRandomValue(20, 60));
        stuff.push_back(j);
    }

    NovaDataDevice::saveData("data.dat", stuff);

    while (window.open()){

        window.start();
        nrd::fill(WHITE);
        window.end();
    }

    window.close();

    return 0;
}
