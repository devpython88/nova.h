#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include <thread>
using nrd = NovaRenderDevice;


class Game : public NovaScene {
    public:
    
    Game(NovaWindow* window): NovaScene(window){}

    void load() override {}
    void unload() override {}
    void draw() override {
        window->start();
        nrd::fill(BLACK);
        window->end();
    }
    void update(float deltaTime) override {
        if (NovaInputDevice::keyHit(NovaEvent::Key::A)){
            NovaScenes::go("menu");
        }
    }
};


class Menu : public NovaScene {
    public:
    
    Menu(NovaWindow* window): NovaScene(window){}

    void load() override {}
    void unload() override {}
    void draw() override {
        window->start();
        nrd::fill(BLUE);
        window->end();
    }
    void update(float deltaTime) override {}
};

int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Game");

    nrd::framerateLimit(24);

    Game game(&window);
    Menu menu(&window);

    NovaScenes::add("game", &game);
    NovaScenes::add("menu", &menu);

    while (window.open()){
        NovaScenes::show();
    }

    window.close();

    return 0;
}
