#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <cstdint>
#include "game.h"

int main(int argc, char* argv[]) {

    //Initialize the game
    if(!InitGame()) {
        std::cout << "Unable to initialize from main!\n";
        CloseShop();
    }

    //Set sprite properties

    //Load background music
    if(!InitMusic()) {
        std::cout << "Music failed to load!\n";
    }

    //Begin Game Loop
    while(ProgramIsRunning()) {
        //Check for input
        const uint8_t* keys = SDL_GetKeyboardState(NULL); //Get keypresses for current frame

        //Game logic here
        //Update sprite states

        RunGame();  //Update and draw the current frame

        //Game logic here


    }//End Game Loop

    CloseShop();
    return 0;
} //END MAIN FUNCTION