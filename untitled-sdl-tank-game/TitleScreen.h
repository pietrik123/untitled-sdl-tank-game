#pragma once

#include "MyTexture.h"

class TitleScreen {
public:
    int titleTextX;
    int heroX;
    int heroFrame;
    int cnt;
    SDL_Surface* background;

    int screenWidth;
    int screenHeight;
    
    MyTexture* titleTex;
    MyTexture* hero;

public:
    TitleScreen(int screenWidth, int screenHeight);
    void loop(SDL_Renderer* renderer);
   
private:
    void init(SDL_Renderer* renderer);
    void cleanup();
};
