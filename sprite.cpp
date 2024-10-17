#include "sprite.h"
#include "settings.h"
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

void Sprite::FillRect(SDL_Rect& rect, int xLocation, int yLocation) {
    rect.x = xLocation;
    rect.y = yLocation;
}

void Sprite::setDirection(const uint8_t* keys){
    if(keys[SDL_SCANCODE_UP]) {
        if(currentDirection != up) {
            currentDirection = up;
        }
    }
    if(keys[SDL_SCANCODE_RIGHT]) {
        if(currentDirection != right) {
            currentDirection = right;
        }
    }
    if(keys[SDL_SCANCODE_DOWN]) {
        if(currentDirection != down) {
            currentDirection = down;
        }
    }
    if(keys[SDL_SCANCODE_LEFT]) {
        if(currentDirection != left) {
            currentDirection = left;
        }
    }
}

void AnimatedSprite::setDirection(const uint8_t* keys){
    if(keys[SDL_SCANCODE_UP]) {
        if(currentDirection != up) {
            currentDirection = up;
            numFrames = NUM_FRAMES_UP;
            currentFrame = 0;
        }
    }
    if(keys[SDL_SCANCODE_RIGHT]) {
        if(currentDirection != right) {
            currentDirection = right;
            numFrames = NUM_FRAMES_RIGHT;
            currentFrame = 0;
        }
    }
    if(keys[SDL_SCANCODE_DOWN]) {
        if(currentDirection != down) {
            currentDirection = down;
            numFrames = NUM_FRAMES_DOWN;
            currentFrame = 0;
        }
    }
    if(keys[SDL_SCANCODE_LEFT]) {
        if(currentDirection != left) {
            currentDirection = left;
            numFrames = NUM_FRAMES_LEFT;
            currentFrame = 0;
        }
    }
}

void Sprite::move() {
    if(currentDirection == up) {
        //Move the sprite up
        y -= currentSpeed;
        //Check for screen edge collision
        keepInBounds();
    }
    if(currentDirection == right) {
        //Move the sprite up
        x += currentSpeed;
        //Check for screen edge collision
        keepInBounds();
    }
    if(currentDirection == down) {
        //Move the sprite up
        y += currentSpeed;
        //Check for screen edge collision
        keepInBounds();
    }
    if(currentDirection == left) {
        //Move the sprite up
        x -= currentSpeed;
        //Check for screen edge collision
        keepInBounds();
    }
    //Create rectangle for sprite placement
    FillRect(rectPlacement, x, y);
}

void AnimatedSprite::move() {
    frameCounter++;

    //Delay the current frame
    if(frameCounter > FRAME_DELAY) {
        frameCounter = 0;
        currentFrame++;
    }
    //If last frame is reached, reset animation
    if(currentFrame > numFrames - 1) {
        currentFrame = 0;
    }

    //Update sprite
    //UP
    if(currentDirection == up) {
        //Advance rectangle to current frame on sheet
        rectUp.x = currentFrame * rectUp.w;
        //Move the sprite up
        y -= currentSpeed;
        //Check for screen edge collision
        keepInBounds();
        //Create temp rectangle to hold the current sprite
        FillRect(tempRect, rectUp.x, rectUp.y);
        //Load the proper texture
        texture = textureSheetUp;
    }
    //RIGHT
    if(currentDirection == right) {
        //Advance rectangle to current frame on sheet
        rectRight.x = currentFrame * rectRight.w;
        //Move the sprite right
        x += currentSpeed;
        //Check for screen edge collision
        keepInBounds();
        //Create temp rectangle to hold the current sprite
        FillRect(tempRect, rectRight.x, rectRight.y);
        //Load the proper texture
        texture = textureSheetRight;
    }
    //DOWN
    if(currentDirection == down) {
        //Advance rectangle to current frame on sheet
        rectDown.x = currentFrame * rectDown.w;
        //Move the sprite down
        y += currentSpeed;
        //Check for screen edge collision
        keepInBounds();
        //Create temp rectangle to hold the current sprite
        FillRect(tempRect, rectDown.x, rectDown.y);
        //Load the proper texture
        texture = textureSheetDown;
    }
    //LEFT
    if(currentDirection == left) {
        //Advance rectangle to current frame on sheet
        rectLeft.x = currentFrame * rectLeft.w;
        //Move the sprite up
        x -= currentSpeed;
        //Check for screen edge collision
        keepInBounds();
        //Create temp rectangle to hold the current sprite
        FillRect(tempRect, rectLeft.x, rectLeft.y);
        //Load the proper texture
        texture = textureSheetLeft;
    }
    //Create rectangle to place sprite on the screen
    FillRect(rectPlacement, x, y);
}

void Sprite::keepInBounds() {
  //Check for right collision
  if(x + width > Settings::SCREEN_WIDTH)   //If the right edge of the sprite touches the screen edge
    x = Settings::SCREEN_WIDTH - width;    //Align with the edge
  //Check for left collision
  if (x < 0)    //If the left edge of sprite touches the screen edge
    x = 0;      //Align wiuth the edge
  //Check for bottom collision
  if(y + height > Settings::SCREEN_HEIGHT)   //IF the sprite touches the bottom edge
    y = Settings::SCREEN_HEIGHT - height;    //Align with the edge
  //Check for upper collision
  if(y < 0)         //If the sprite touches the top edge
    y = 0;          //Align with the edge
}