#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "settings.h"
#include "sprite.h"
#include "game.h"
using namespace std;


int main(int argc, char* argv[]) {

    //Initialize the game
    if(!InitGame()) {
        std::cout << "Unable to initialize from main!\n";
        CloseShop();
    }

    //Create all game images
    CreateGameImages();

    //Load background music
    if(!InitMusic()) {
        std::cout <<"Music failed to load!\n";
    }

    //Begin Game Loop
    while(ProgramIsRunning()) {
        //Check for input
        const Uint8* keys = SDL_GetKeyboardState(NULL); //Pass a reference to the keypresses

        //Update sprite states
        //Draw the screen

    }//End Game Loop

    CloseShop();
    return 0;
} //END MAIN FUNCTION


