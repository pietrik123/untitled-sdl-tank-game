#pragma once

class Player;
class MyTexture;
struct SDL_Renderer;

class HUD
{
public:
    MyTexture* helpScreen;
    MyTexture* bombInfo;
    MyTexture* cannonInfo;

    float helpScreenPosX, helpScreenPosY;
    float weaponScreenPosX, weaponScreenPosY;

    void display(SDL_Renderer* renderer, const Player& player);

    HUD();
    HUD(MyTexture* textureHelpScreen, MyTexture* textureBombInfo, MyTexture* textureCannonInfo);
};