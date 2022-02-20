#include "HUD.h"
#include "MyTexture.h"
#include "Player.h"
#include "weapon.h"
#include "MyText.h"
#include "PlayerHealthBar.h"

#include <string>

void HUD::initScoreText(SDL_Renderer * renderer, TTF_Font * font, const SDL_Color & c)
{
    scoreText = new MyText(renderer, font, c);
}

void HUD::initCurrentWeaponInfoText(SDL_Renderer * renderer, TTF_Font * font, const SDL_Color & c)
{
    currentWeaponInfoText = new MyText(renderer, font, c);
}

void HUD::initHealthBar(const Player& p)
{
    healthBar = new PlayerHealthBar(p);
}

void HUD::display(int scorePosX, int scorePosY, 
    int ammoPosX, int ammoPosY,
    TTF_Font* font,
    SDL_Renderer* renderer, const Player& player)
{
    if (!scoreText || !currentWeaponInfoText || !healthBar)
    {
        std::cout << "HUD display error! Uninitialized fields!\n";
        exit(EXIT_FAILURE);
    }

    if (player.weaponIndex == WeaponId::BASIC_CANNON)
    {
        cannonInfo->render(renderer, static_cast<int>(weaponScreenPosX), static_cast<int>(weaponScreenPosY),
            MyTexture::RENDER_IN_CENTER);
    }
    else if (player.weaponIndex == WeaponId::BOMB_DROP)
    {
        bombInfo->render(renderer, static_cast<int>(weaponScreenPosX), static_cast<int>(weaponScreenPosY),
            MyTexture::RENDER_IN_CENTER);
    }
    else {}

    helpScreen->render(renderer, static_cast<int>(helpScreenPosX), static_cast<int>(helpScreenPosY),
        MyTexture::RENDER_IN_CENTER); 

    scoreText->printText("score: " + std::to_string(player.coinsCollected), scorePosX, scorePosY,
        renderer, font, { 255, 255, 255, 255 });

    std::string weaponName;
    // TODO display weapon and ammo information
    if (player.weaponIndex == WeaponId::BASIC_CANNON)
    {
        weaponName = "Cannon";
    }
    else if (player.weaponIndex == WeaponId::BOMB_DROP)
    {
        weaponName = "Bomb";
    }

    currentWeaponInfoText->printText(weaponName + ":   " +
        std::to_string(player.getCurrentWeapon()->getAmmo()),
        ammoPosX, ammoPosY, renderer, font, { 255, 255, 255 });

    healthBar->display(0, 0, renderer, 1.5);
}

HUD::HUD(){}

HUD::HUD(MyTexture* textureHelpScreen, MyTexture* textureBombInfo, MyTexture* textureCannonInfo)
{
    //help windows positioning
    helpScreenPosX = 320;
    helpScreenPosY = 450;
    weaponScreenPosX = helpScreenPosX-195;
    weaponScreenPosY = 450;

    //help windwos texture loading
    helpScreen = textureHelpScreen;
    bombInfo = textureBombInfo;
    cannonInfo = textureCannonInfo;

    scoreText = nullptr;
    currentWeaponInfoText = nullptr;
    healthBar = nullptr;
}

HUD::~HUD()
{
    std::cout << "Destroying hud\n";
    if (scoreText) delete scoreText;
    if (currentWeaponInfoText) delete currentWeaponInfoText;
    if (healthBar) delete healthBar;
}