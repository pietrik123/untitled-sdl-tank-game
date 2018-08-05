#pragma once
#include "MyTexture.h"
#include "Player.h"

class HUD
{
public:
    MyTexture helpScreen;
    MyTexture bombInfo;
    MyTexture cannonInfo;

    float helpScreenPosX, helpScreenPosY;
    float weaponScreenPosX, weaponScreenPosY;


    void display(SDL_Renderer* renderer, const Player& player);

    HUD();
    HUD(MyTexture& textureHelpScreen, MyTexture& textureBombInfo, MyTexture& textureCannonInfo);
};