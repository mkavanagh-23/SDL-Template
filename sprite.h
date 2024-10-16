#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "game.h"

//Enum type to refer to directions by name
enum Direction {
  north,        // == 0
  east,         // == 1
  south,        // == 2
  west          // == 3
};

//Enum type to hold R,G,B values as one
struct RGB {
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

//Hold all varibles and functions for sprites
class Sprite {
    public:
        static SDL_Surface* tempSurface;    //Static: we only want one temp object for copying all surface textures
    private:
};

//And some additional members if the sprite is animated
class AnimatedSprite : public Sprite {      //Inherits from class "Sprite"
    public:
    private:
};

#endif