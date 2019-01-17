#include "HUD.h"
#include "MyTexture.h"
#include "Player.h"
#include "weapon.h"

class SDL_Renderer;

void HUD::display(SDL_Renderer* renderer, const Player& player)
{
    if (player.weaponIndex == WeaponId::BASIC_CANNON)
    {
        cannonInfo->render(renderer, (int)weaponScreenPosX, (int)weaponScreenPosY, MyTexture::RENDER_IN_CENTER);
    }
    else if (player.weaponIndex == WeaponId::BOMB_DROP)
    {
        bombInfo->render(renderer, (int)weaponScreenPosX, (int)weaponScreenPosY, MyTexture::RENDER_IN_CENTER);
    }
    else {}

    helpScreen->render(renderer, (int)helpScreenPosX, (int) helpScreenPosY, MyTexture::RENDER_IN_CENTER);
     
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
}

