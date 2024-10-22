#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

//Declare gameplay varibales
extern SDL_Window* gameWindow;
extern SDL_Renderer* renderer;

extern Mix_Music* GameMusic;

extern int scorePlayer1;
extern int scorePlayer2;

//Function prototypes
bool InitSDL();
bool InitGame();
bool InitMusic();
bool ProgramIsRunning();
void RunGame();
void DrawGame();
void ResetGame();
void CloseShop();

#endif