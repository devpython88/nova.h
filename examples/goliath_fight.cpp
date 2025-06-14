/***************************************************************/
/*                                                              */
/*       EXAMPLE: GOLIATH FIGHT                                 */
/*       PASTE IN MAIN.CPP TO TEST                              */
/*       BUTTON SMASH THE X AND Z KEY TO INCREASE POWER         */
/*                                                              */
/***************************************************************/



#include <iostream>
#include "nova.h"
#include "novamisc.h"
#include "novatime.h"

#include <thread>
using nrd = NovaRenderDevice;

int main(int argc, char const *argv[])
{
    NovaWindow window(800, 600, "Button Smasher");

    nrd::framerateLimit(60);

    NovaEvent event; // to keep event

    int powerLevel = 0; // our power level
    int goliathPowerLevel = 10000; // goliaths power level, can be customized

    // Just for preferences
    float goliathX = 200, goliathY = 70;
    float playerX = 200, playerY = 300;
    
    float goliathWidth = 60, goliathHeight = 60;
    float playerWidth = 20, playerHeight = 20;

    // End of preferences

    // Make goliath and player
    NovaRectangle goliath(goliathX, goliathY, goliathWidth, goliathHeight, RED);
    NovaRectangle player(playerX, playerY, playerWidth, playerHeight, GREEN);

    // Timer for fight
    NovaTimer fightTimer(20.0f); // Change `20.0f` to change fight 

    // Randomizer
    NovaRandomDevice rd;


    // Flags
    bool lost = false, won = false;

    while (window.open()){
        event.fetch(); // get event

        // Handle button smash
        if ((event.lastKeyHit == NovaEvent::Key::Z
            || event.lastKeyHit == NovaEvent::Key::X) && !fightTimer.done()){
            powerLevel += rd.randomInt(20, 120);
        }

        // Update timer
        fightTimer.update();

        // Handle player movement once timer complete
        if (fightTimer.done()){
            player.moveTo(NovaVec2(goliathX, goliathY), 2.0f); // 2.0f is the speed
        }

        // Handle collision
        if (nrd::checkCollision(goliath, player)){
            if (powerLevel >= goliathPowerLevel) won = true;
            else lost = true;
        }

        window.start();
        nrd::fill(BLUE);

        // Draw goliath and player
        nrd::rect(goliath);
        nrd::rect(player);

        // Draw power level

        std::stringstream ss;
        ss << "Goliath: " << goliathPowerLevel << "\n"
            << "You: " << powerLevel;
        
        nrd::text(ss.str(), 20, 450, 32, BLACK);

        // Draw timer

        std::stringstream ss2;
        ss2 << "Time left: " << static_cast<int>(fightTimer.duration - fightTimer.elapsed()) << "s";

        nrd::text(ss2.str(), 120, 70, 32, BLACK);



        // Draw dialogs
        if (lost){
            nrd::rect(50, 50, 400, 300, BLACK);
            nrd::text("You lost", 120, 80, 32, WHITE);
        }
        
        else if (won){
            nrd::rect(50, 50, 400, 300, BLACK);
            nrd::text("You won", 120, 80, 32, WHITE);
        }
        window.end();
    }

    window.close();

    return 0;
}
