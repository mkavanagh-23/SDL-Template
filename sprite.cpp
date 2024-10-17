#include "sprite.h"
#include <SDL2/SDL_surface.h>
#include <string>
#include <iostream>
#include <cassert>

SDL_Surface* Sprite::tempSurface{NULL};

RGB Sprite::HexToRGB(const std::string& hex) {
    //Create temporary color objects
    std::string hexColor = hex;
    assert(hexColor.length() == 6 && "Provided colorKey not a valid hex code.\n");
    RGB rgbColor;

    //Extract sets of two characters and convert to RGB values
    rgbColor.r = static_cast<uint8_t>(std::stoi(hexColor.substr(0,2), nullptr, 16));
    rgbColor.g = static_cast<uint8_t>(std::stoi(hexColor.substr(2,2), nullptr, 16));
    rgbColor.b = static_cast<uint8_t>(std::stoi(hexColor.substr(4,2), nullptr, 16));

    return rgbColor;
}

SDL_Surface* Sprite::LoadImage(const char* path) {
    tempSurface = SDL_LoadBMP(path);
    if(tempSurface == NULL) {
        std::cout << "Unable to load image from path: " << path << '\n';
    }
    return tempSurface;
}

SDL_Texture* Sprite::LoadTexture() {
    SDL_Texture* newTexture{NULL};

    newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if(newTexture == NULL) {
        std::cout << "Unable to create texture.\n";
    }

    SDL_FreeSurface(tempSurface);
    return newTexture;
}

void Sprite::setTransparentColor(){
    //Create the colorkey
    uint32_t colorKey;
    colorKey = SDL_MapRGB(tempSurface->format, TRANSPARENCY_MASK.r, TRANSPARENCY_MASK.g, TRANSPARENCY_MASK.b);

    //Set colorkey as transparent color
    SDL_SetColorKey(tempSurface, SDL_TRUE, colorKey);
}

void Sprite::FillRect() {
    rectPlacement.x = x;
    rectPlacement.y = y;
}