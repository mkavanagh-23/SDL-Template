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

    //Create all game images
    CreateGameImages();

    //Set sprite properties

    //Load background music
    if(!InitMusic()) {
        std::cout << "Music failed to load!\n";
    }

    //Begin Game Loop
    while(ProgramIsRunning()) {
        //Check for input
        const uint8_t* keys = SDL_GetKeyboardState(NULL); //Pass the keypresses

        //Update sprite states

        //Draw the screen


    }//End Game Loop

    CloseShop();
    return 0;
} //END MAIN FUNCTION