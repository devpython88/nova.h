#include <iostream>
#include "nova.h"
#include "novajson.h"

using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(640, 480, "Game");

    NovaJSON json;
    json.loadFile("test.json");
    nlohmann::json hobbies = json.get<nlohmann::json>("Hobbies");
    hobbies.push_back("Hello");

    json.set<nlohmann::json>("Hobbies", hobbies);

    json.writeFile("newjson.json");

    while (window.open()){

        window.start();
        nrd::fill(WHITE);

        window.end();
    }

    return 0;
}
