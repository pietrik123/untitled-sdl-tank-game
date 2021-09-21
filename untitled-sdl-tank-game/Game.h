#pragma once

#include "Level.h"
#include "TextureDataStruct.h"
#include "menu.h"

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#include<vector>

class Game
{
public:
    // SDL fields
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screenSurface;
    Mix_Music *music;
    TTF_Font* ttfFont;

    // GUI (menu etc.)
    GameMenu gameMenu;
    
    // Level
    Level* lev;
    
    // texture struct	
    TextureDataStruct texDataStruct;

    // other
    int screenWidth;
    int screenHeight;

    float scaleX; // screen_dx/world_dx
    float scaleY; // screen_dy/world_dy

    unsigned long int mainLoopCnt = 0;

    Game();
    ~Game();

    bool initSDL();

    void loadTextures();
    void createGameMenu();
    bool initGame();
    bool runGame();
    void setLevel(Level* l);

    bool endGame();
    
    // utils
    /**
     * get X coord in screen axis system
     * \param localPosX - x coord in local axis system
     */
    int getPosXOnScreen(float localPosX);
    /**
     * get Y coord in screen axis system
     * \param localPosX - y coord in local axis system
     */
    int getPosYOnScreen(float localPosY);
};

