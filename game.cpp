#include "game.h"
#include "settings.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

//Instantiate Window, Renderer, and tempSurface
SDL_Window* gameWindow{NULL};
SDL_Renderer* renderer{NULL};

//Setup buffer for BG music
Mix_Music *GameMusic = NULL;

//Define gameplay variables
int scorePlayer1{0};
int scorePlayer2{0};

//Function prototypes
bool InitSDL();
bool InitGame();

bool InitMusic() {
    //Load background music
    GameMusic = Mix_LoadMUS(std::string(Settings::BG_MUSIC).c_str());
    //Error check music
    if(GameMusic == NULL)
       return false;
    Mix_PlayMusic(GameMusic, -1);
    return true;    
}

bool ProgramIsRunning();
void CreateGameImages();
void RunGame();

void DrawGame() {
    //Clear the window
    SDL_RenderClear(renderer);
    //Copy the background
    SDL_RenderCopy(renderer, background.texture, NULL, &background.rectPlacement);
    //Copy the sprite
    SDL_RenderCopy(renderer, sprite.texture, &sprite.tempRect, &sprite.rectPlacement);
    //display the game screen with updated position of Zombie
    SDL_RenderPresent(renderer);
    SDL_Delay(5);  //delay a bit
}

void ResetGame();
void CloseShop();