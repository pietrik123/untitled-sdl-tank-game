#pragma once

class Player;
class MyTexture;
class MyText;
class PlayerHealthBar;

struct SDL_Renderer;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;
struct SDL_Color;

class HUD
{
public:
    MyTexture* helpScreen;
    MyTexture* bombInfo;
    MyTexture* cannonInfo;

    MyText* scoreText;
    MyText* currentWeaponInfoText;
    PlayerHealthBar* healthBar;

    float helpScreenPosX, helpScreenPosY;
    float weaponScreenPosX, weaponScreenPosY;

    void initScoreText(SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& c);
    void initCurrentWeaponInfoText(SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& c);
    void initHealthBar(const Player & p);

    void display(int scorePosX, int scorePosY, int ammoPosX, int ammoPosY, TTF_Font * font, SDL_Renderer * renderer, const Player & player);

    HUD();
    HUD(MyTexture* textureHelpScreen, MyTexture* textureBombInfo, MyTexture* textureCannonInfo);
    virtual ~HUD();
};