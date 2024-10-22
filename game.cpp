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
bool InitSDL() {
     //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL failed to initialize!\n");
        SDL_Quit();
    }
    //Init audio subsystem
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1)
    {
        printf("Open Audio failed to initialize!\n");
        return false;
    }
    return true;
}

bool InitGame() {
    //Init SDL
    if(!InitSDL())
        return false;

    //Initiatialize game variables
    return true;
}


bool InitMusic() {
    //Load background music
    GameMusic = Mix_LoadMUS(std::string(Settings::BG_MUSIC).c_str());
    //Error check music
    if(GameMusic == NULL)
       return false;
    Mix_PlayMusic(GameMusic, -1);
    return true;    
}

bool ProgramIsRunning() {
    SDL_Event event;
    bool running = true;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            running = false;
    }
    return running;
};

void CreateGameImages();
void RunGame();

void DrawGame() {
    //Clear the window
    SDL_RenderClear(renderer);
    //Copy the background
    SDL_RenderCopy(renderer, background.texture, NULL, &background.rectPlacement);          // void Sprite::copyToRender(); ???
    //Copy the sprite
    SDL_RenderCopy(renderer, sprite.texture, &sprite.tempRect, &sprite.rectPlacement);
    //display the game screen with updated position of Zombie
    SDL_RenderPresent(renderer);
    SDL_Delay(5);  //delay a bit
}

void ResetGame();
void CloseShop();