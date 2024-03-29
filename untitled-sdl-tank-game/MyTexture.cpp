#include "MyTexture.h"

#include <iostream>
#include <stdlib.h>

MyTexture::MyTexture()
{
    sdlTexture = nullptr;
    std::cout << __FUNCTION__ << " : MyTexture::MyTexture() : Empty texture created!" << std::endl;
}

MyTexture::MyTexture(SDL_Renderer* renderer, std::string fileName)
{

    SDL_Surface* textureSurface = nullptr;

    textureSurface = IMG_Load(fileName.c_str());
    if (textureSurface == nullptr)
    {
        std::cout << __FUNCTION__ << " : MyTexture::MyTexture() : Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_SetColorKey(textureSurface, SDL_TRUE, SDL_MapRGB(textureSurface->format, 0xFF, 0x00, 0xFF));

    sdlTexture = SDL_CreateTextureFromSurface(renderer, textureSurface);
    if (sdlTexture == nullptr)
    {
        std::cout << __FUNCTION__ << " : MyTexture::MyTexture() : Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(textureSurface);
    std::cout << __FUNCTION__ << " : MyTexture::MyTexture() : Texture created!" << std::endl;
}

MyTexture::~MyTexture()
{
    // TODO this needs to be thought over.
    // For now destroying texture results in segmentation faults.
    // SDL_DestroyTexture(texture);
    std::cout << __FUNCTION__ << " : MyTexture::~MyTexture() : Destructor called!" << std::endl;
}

bool MyTexture::loadTextTexture(const std::string& text, const SDL_Color& color, SDL_Renderer* renderer, TTF_Font* ttfFont)
{
    //free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(ttfFont, text.c_str(), color);
    if (textSurface == nullptr)
    {
        std::cout << __FUNCTION__ << " : Error in creating text surface\n";
        return false;
    }

    sdlTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (sdlTexture == nullptr)
    {
        std::cout << __FUNCTION__ << " : Error in creating texture out of text surface\n";
        return false;
    }
    
    SDL_FreeSurface(textSurface);

    return true;
}

void MyTexture::render(SDL_Renderer* renderer, int x, int y, RenderMode mode)
{
    SDL_Rect rect;

    int w, h;

    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &w, &h);

    if (mode == RENDER_IN_CENTER)
    {
        rect.x = x - w / 2;
        rect.y = y - h / 2;
    }
    else if (mode == RENDER_IN_CORNER)
    {
        rect.x = x;
        rect.y = y;
    }
    else
    {
        std::cout << __FUNCTION__ << " : MyTexture::render() Incorrect mode used for rendering!\n";
    }

    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer, sdlTexture, nullptr, &rect);
}

void MyTexture::renderAnim(SDL_Renderer* renderer, int x, int y, RenderMode mode, int numOfFrames, int frameIndex)
{
    SDL_Rect targetRect;
    SDL_Rect sourceRect;

    int w, h;

    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &w, &h);
    int tileWidth = w / numOfFrames;

    sourceRect.x = frameIndex*tileWidth;
    sourceRect.y = 0;
    sourceRect.w = tileWidth;
    sourceRect.h = h;

    if (mode == RENDER_IN_CENTER)
    {
        targetRect.x = x - tileWidth / 2;
        targetRect.y = y - h / 2;
    }
    else if (mode == RENDER_IN_CORNER)
    {
        targetRect.x = x;
        targetRect.y = y;
    }
    else
    {
        std::cout << __FUNCTION__ << " : MyTexture::renderAnim() Incorrect mode used for rendering!\n";
    }

    targetRect.w = tileWidth;
    targetRect.h = h;

    SDL_RenderCopy(renderer, sdlTexture, &sourceRect, &targetRect);
}

void MyTexture::render(SDL_Renderer* renderer, int x, int y, RenderMode mode, 
    float angle)
{
    SDL_Rect rect;

    int w, h;

    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &w, &h);

    if (mode == RENDER_IN_CENTER)
    {
        rect.x = x - w / 2;
        rect.y = y - h / 2;
    }
    else if (mode == RENDER_IN_CORNER)
    {
        rect.x = x;
        rect.y = y;
    }
    else
    {
        std::cout << __FUNCTION__ << " : MyTexture::render() Incorrect mode used for rendering!\n";
    }

    rect.w = w;
    rect.h = h;

    SDL_RenderCopyEx(renderer, sdlTexture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

std::pair<int,int> MyTexture::getTextureWidthAndHeight()
{
    int w, h;
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &w, &h);
    return std::pair<int, int>(w,h);
}