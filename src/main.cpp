#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;


int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Game");

    nrd::framerateLimit(24);

    NovaList<int> ages;
    
    ages.push_back(23);
    ages.push_back(19);
    ages.push_back(3);
    ages.push_back(13);
    try { ages.find_item(223); } catch(std::exception e){}

    while (window.open()){
        window.start();
        nrd::fill(WHITE);
        window.end();
    }

    window.close();

    return 0;
}
