#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>
#include "game.h"
#include "settings.h"

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
        RGB transparencyMask{};        //ColorKey for sprite background transparency

        //Movement variables
        int currentSpeed;                   //How many pixels to move the sprite by
        Direction currentDirection{still};         //Current direction of motion

    public:
    //Constructors
        //Default constructor
        Sprite();
        //No transparency
        Sprite(const char* filePath);
        //Transparency
        Sprite(const char* filePath, RGB colorKey);
        Sprite(const char* filePath, std::string colorHex);
        
    //Destructor
        ~Sprite();

        virtual void copyToRender();

    protected:
        //Function Prototypes
        void FillRect(SDL_Rect& rect, int xLocation, int yLocation);    //Create a rectangle at the given position
        SDL_Surface* LoadImage(const char* path);                   //Load image onto surface
        SDL_Texture* LoadTexture();                              //Load surface onto texture
        void setTransparentColor();                              //Set transparency

        void keepInBounds();                            //Check for border collision and move to edge

        virtual void setDirection(const uint8_t* keys);         //Set the sprite's current direction
        virtual void move();                                //move the sprite
    
    private:
        void create();
        void createTransparent();
};

//And some additional members if the sprite is animated
class AnimatedSprite 
: public Sprite {      //Inherits from class "Sprite"
    public:
    private:
        //Instantiate FRAME_DELAY on a per-sprite basis to control animation speed
        const int FRAME_DELAY {200 / Settings::FPS};
        const int NUM_FRAMES{};         //Total number of frames for generic sprite

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

        //Rectangles - MAKE SURE TO SET WIDTHS/HEIGHTS IN CONSTRUCTOR!!!!
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
        int numFrames;               //Holds number of frames in current strip
        int currentFrame{0};         //Current frame in animation strip
        int frameCounter{0};         //frame delay
        int sheetWidth, sheetHeight;
    public:
        //Constructors
        AnimatedSprite() = delete;

        //No transparency
        AnimatedSprite(const char* filepathUp, const char* filepathRight, const char* filepathDown, const char* filepathLeft, const int numFrames);

        //Transparency
        AnimatedSprite(const char* filepathUp, const char* filepathRight, const char* filepathDown, const char* filepathLeft, const int numFrames, RGB colorKey);
        AnimatedSprite(const char* filepathUp, const char* filepathRight, const char* filepathDown, const char* filepathLeft, const int numFrames, std::string colorHex);

        //Destructor
        ~AnimatedSprite();

        //Function prototypes
        void setDirection(const uint8_t* keys);
        void move();
        void copyToRender();
    
    private:
        void create(const char* filepath, SDL_Texture* texture, SDL_Rect& rectSheet, SDL_Rect& rectSprite);
        void createTransparent(const char* filepath, SDL_Texture* texture, SDL_Rect& rectSheet, SDL_Rect& rectSprite);

};

#endif