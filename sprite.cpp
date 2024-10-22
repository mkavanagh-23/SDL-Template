#include <SDL2/SDL_render.h>
#include <string>
#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include "sprite.h"
#include "game.h"
#include "settings.h"

SDL_Surface* Sprite::tempSurface{NULL};

//Constructors
//No transparency sprite object
Sprite::Sprite(const char* filePath)
    : PATH{filePath}
{
    create();
}

//Transparent sprite objects
Sprite::Sprite(const char* filePath, RGB colorKey)
    : PATH{filePath}, transparencyMask{colorKey}
{
    createTransparent();
}

//Transparent sprite object
Sprite::Sprite(const char* filePath, std::string colorHex)
    : Sprite::Sprite(filePath, HexToRGB(colorHex))  //Convert hex to RGB to use in constructor
{}
    
//Destructor
Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

//Constructors
//No transparency
AnimatedSprite::AnimatedSprite(const char* filepathUp, const char* filepathRight, const char* filepathDown, const char* filepathLeft, const int numFrames)
    : Sprite(), PATH_SHEET_UP{filepathUp}, PATH_SHEET_RIGHT{filepathRight}, PATH_SHEET_DOWN{filepathDown}, PATH_SHEET_LEFT{filepathLeft}, NUM_FRAMES{numFrames}
{
    //Create up
    create(PATH_SHEET_UP, textureSheetUp, rectSheetUp, rectUp);
    //Create right
    create(PATH_SHEET_RIGHT, textureSheetRight, rectSheetRight, rectRight);
    //Create down
    create(PATH_SHEET_DOWN, textureSheetDown, rectSheetDown, rectDown);
    //Create left
    create(PATH_SHEET_LEFT, textureSheetLeft, rectSheetLeft, rectLeft);
}

//Transparency
AnimatedSprite::AnimatedSprite(const char* filepathUp, const char* filepathRight, const char* filepathDown, const char* filepathLeft, const int numFrames, RGB colorKey) 
    : Sprite(), PATH_SHEET_UP{filepathUp}, PATH_SHEET_RIGHT{filepathRight}, PATH_SHEET_DOWN{filepathDown}, PATH_SHEET_LEFT{filepathLeft}, NUM_FRAMES{numFrames}
{
    transparencyMask = colorKey;
    //Create up
    createTransparent(PATH_SHEET_UP, textureSheetUp, rectSheetUp, rectUp);
    //Create right
    createTransparent(PATH_SHEET_RIGHT, textureSheetRight, rectSheetRight, rectRight);
    //Create down
    createTransparent(PATH_SHEET_DOWN, textureSheetDown, rectSheetDown, rectDown);
    //Create left
    createTransparent(PATH_SHEET_LEFT, textureSheetLeft, rectSheetLeft, rectLeft);
}
AnimatedSprite::AnimatedSprite(const char* filepathUp, const char* filepathRight, const char* filepathDown, const char* filepathLeft, const int numFrames, std::string colorHex)
    : AnimatedSprite(filepathUp, filepathRight, filepathDown, filepathLeft, numFrames, HexToRGB(colorHex))
{}

//Destructor
AnimatedSprite::~AnimatedSprite() {     //No explicit call to base class destructor, it is implict
    SDL_DestroyTexture(textureSheetUp);
    SDL_DestroyTexture(textureSheetRight);
    SDL_DestroyTexture(textureSheetDown);
    SDL_DestroyTexture(textureSheetLeft);
}

SDL_Surface* Sprite::LoadImage(const char* path) {
    tempSurface = SDL_LoadBMP(path);
    if(tempSurface == NULL) {
        std::cout << "Unable to load image from path: \"" << path << "\"\n";
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
    colorKey = SDL_MapRGB(tempSurface->format, transparencyMask.r, transparencyMask.g, transparencyMask.b);

    //Set colorkey as transparent color
    SDL_SetColorKey(tempSurface, SDL_TRUE, colorKey);
}

void Sprite::FillRect(SDL_Rect& rect, int xLocation, int yLocation) {
    rect.x = xLocation;
    rect.y = yLocation;
}

void Sprite::create() {
    //Crerate temp surface from bitmap
    tempSurface = LoadImage(PATH);
    //Load surface into a texture
    texture = LoadTexture();
    //Get width and height of texture
    SDL_QueryTexture(texture, NULL, NULL, &rectPlacement.w, &rectPlacement.h);
    width = rectPlacement.w;
    height = rectPlacement.h;
    //Fill the rectangle wih the texture
    FillRect(rectPlacement, x, y);
}

void Sprite::createTransparent() {
    //Crerate temp surface from bitmap
    tempSurface = LoadImage(PATH);
    //Set transparency mask
    setTransparentColor();
    //Load surface into a texture
    texture = LoadTexture();
    //Get width and height of texture
    SDL_QueryTexture(texture, NULL, NULL, &rectPlacement.w, &rectPlacement.h);
    width = rectPlacement.w;
    height = rectPlacement.h;
    //Fill the rectangle wih the texture
    FillRect(rectPlacement, x, y);
}

void AnimatedSprite::create(const char* filepath, SDL_Texture* texture, SDL_Rect& rectSheet, SDL_Rect& rectSprite) {
    tempSurface = LoadImage(filepath);
    //Create a texture from the surface
    texture = LoadTexture();
    //Get the width and height of the texture sheet
    SDL_QueryTexture(texture, NULL, NULL, &rectSheet.w, &rectSheet.h);
    width = rectSheet.w / NUM_FRAMES;
    height = rectSheet.h;
    //Create the rectangle for upward-facing sprite
    FillRect(rectSprite, x, y);
}

void AnimatedSprite::createTransparent(const char* filepath, SDL_Texture* texture, SDL_Rect& rectSheet, SDL_Rect& rectSprite) {
    tempSurface = LoadImage(filepath);
    setTransparentColor();
    texture = LoadTexture();
    SDL_QueryTexture(texture, NULL, NULL, &rectSheet.w, &rectSheet.h);
    width = rectSheet.w / NUM_FRAMES;
    height = rectSheet.h;
    FillRect(rectSprite, x, y);
}

void Sprite::copyToRender() {
    SDL_RenderCopy(renderer, texture, NULL, &rectPlacement);
}
void AnimatedSprite::copyToRender() {
    SDL_RenderCopy(renderer, texture, &tempRect, &rectPlacement);
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
//            numFrames = NUM_FRAMES_UP;
            currentFrame = 0;
        }
    }
    if(keys[SDL_SCANCODE_RIGHT]) {
        if(currentDirection != right) {
            currentDirection = right;
//            numFrames = NUM_FRAMES_RIGHT;
            currentFrame = 0;
        }
    }
    if(keys[SDL_SCANCODE_DOWN]) {
        if(currentDirection != down) {
            currentDirection = down;
//            numFrames = NUM_FRAMES_DOWN;
            currentFrame = 0;
        }
    }
    if(keys[SDL_SCANCODE_LEFT]) {
        if(currentDirection != left) {
            currentDirection = left;
//            numFrames = NUM_FRAMES_LEFT;
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