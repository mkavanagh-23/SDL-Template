#include "game.h"
#include "settings.h"
#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

//Instantiate Window, Renderer, and tempSurface
SDL_Window* gameWindow{NULL};
SDL_Renderer* renderer{NULL};

//Setup buffer for BG music
Mix_Music *GameMusic = NULL;

//Define gameplay variables
int scorePlayer1{0};
int scorePlayer2{0};

//Initialize sprites
//Background
Sprite background{"relative/path/to/background.bmp"};
//Sprite
AnimatedSprite sprite{"/path/up.bmp", "/path/right.bmp", "/path/down.bmp", "/path/left.bmp", 1, "HexKey"};

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
    gameWindow = SDL_CreateWindow(Settings::TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);
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

void RunGame();

void DrawGame() {
    //Clear the window
    SDL_RenderClear(renderer);
    //Copy the background
    background.copyToRender();
    //Copy the sprite
    sprite.copyToRender();
    //display the game screen
    SDL_RenderPresent(renderer);
    SDL_Delay(5);  //delay a bit
}

void ResetGame();
void CloseShop();