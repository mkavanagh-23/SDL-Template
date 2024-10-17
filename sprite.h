#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>
#include "game.h"
#include "settings.h"

//Enum type to refer to movement directions by name
enum Direction {
  up,       // == 0
  right,    // == 1
  down,     // == 2
  left,     // == 3
  still     // == 4
};

//Enum type to hold R,G,B color values as one object (default white)
struct RGB {
    uint8_t r{255};
    uint8_t g{255};
    uint8_t b{255};
};

//Hold all varibles and functions for sprites
class Sprite {
    public:
    protected:
        //Surface for Creating Textures
        static SDL_Surface* tempSurface;    //Static: we only want one temp object for copying all surface textures
        
        //File path
        const char* PATH;

        //Texture variables
        SDL_Texture* texture;               //Pointer to sprite texture
        SDL_Rect rectPlacement;             //Rectangle to render the sprite at a position on screen

        //Sprite attributes
        int width, height;            //Sprite width and height
        int x, y;                           //Sprite x and y coordinates
        const RGB TRANSPARENCY_MASK{};        //ColorKey for sprite background transparency

        //Movement variables
        int currentSpeed;                   //How many pixels to move the sprite by
        Direction currentDirection;         //Current direction of motion
    public:
    //Constructors
        //Delete the default, we at least need a file path!
        Sprite() = delete;
        //No transparency sprite object
        Sprite(const char* filePath)
            : PATH{filePath}
        {
            //Crerate temp surface from bitmap
            tempSurface = LoadImage(PATH);
            //Load surface into a texture
            texture = LoadTexture();
            //Get width and height of texture
            SDL_QueryTexture(texture, NULL, NULL, &rectPlacement.w, &rectPlacement.h);
            width = rectPlacement.w;
            height = rectPlacement.h;
            //Fill the rectangle wih the texture
            FillRect();
        }
        //Transparent sprite object
        Sprite(const char* filePath, std::string colorHex)
            : PATH{filePath}
        {}
    //Destructor
        ~Sprite()
        {
            PATH = NULL;
            SDL_DestroyTexture(texture);
        }
    protected:
        //Function Prototypes
        virtual void FillRect();
        SDL_Surface* LoadImage(const char* path);
        SDL_Texture* LoadTexture();
        SDL_Surface* setTransparentColor();
        RGB HexToRGB(const std::string& hex);   //Convert hex color codes to RGB color object
        void updateDirection();
        void move();
    private:
};

//And some additional members if the sprite is animated
class AnimatedSprite : public Sprite {      //Inherits from class "Sprite"
    public:
    private:
        //Instantiate FRAME_DELAY on a per-sprite basis to control animation speed
        const int FRAME_DELAY {200 / Settings::FPS};
        const int NUM_FRAMES{};         //Total number of frames for generic sprite
        const int NUM_FRAMES_UP{};      //Total number of frames in "Up" sprite strip
        const int NUM_FRAMES_RIGHT{};   //Total number of frames in "Right" sprite strip
        const int NUM_FRAMES_DOWN{};    //Total number of frames in "Down" sprite strip
        const int NUM_FRAMES_LEFT{};    //Total number of frames in "Left" sprite strip

        //File paths
        const char* PATH_SHEET_UP{NULL};
        const char* PATH_SHEET_RIGHT{NULL};
        const char* PATH_SHEET_DOWN{NULL};
        const char* PATH_SHEET_LEFT{NULL};

        //Textures
        SDL_Texture* textureSheetUp;        //Pointer to texture for "Up" animation     
        SDL_Texture* textureSheetRight;     //Pointer to texture for "Right" animation     
        SDL_Texture* textureSheetDown;      //Pointer to texture for "Down" animation     
        SDL_Texture* textureSheetLeft;      //Pointer to texture for "Left" animation     

        //Rectangles
        SDL_Rect rectSheet;                 //Rectangle for current player direction sheet
        SDL_Rect rectSheetUp;               //Rectangle for upward sheet
        SDL_Rect rectSheetRight;            //Rectangle for right sheet
        SDL_Rect rectSheetDown;             //Rectangle for downward sheet
        SDL_Rect rectSheetLeft;             //Rectangle for left sheet

        SDL_Rect rectUp;                    //Rectangle for single upward-facing sprite
        SDL_Rect rectRight;                 //Rectangle for single right-facing sprite
        SDL_Rect rectDown;                  //Rectangle for single downard-facing sprite
        SDL_Rect rectLeft;                  //Rectangle for single left-facing sprite

        SDL_Rect tempRect;                  //Rectangle to hold single sprite before moving to rectPlacement

        //Animation variables
        const int numFrames;                      //Holds number of frames in current strip
        int currentFrame{0};               //Current frame in animation strip
};

#endif