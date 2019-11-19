#include "Crate.h"
#include "GameObject.h"
#include "Player.h"
#include "ObjectAdder.h"

#include <random>

Crate::Crate() {};

Crate::Crate(float x, float y, float parRadius, MyTexture* texture)
{
    packageContent = static_cast<GoodsId>(rand() % 3);

    posX = x;
    posY = y;
    radius = parRadius;
    myTex = texture;
    direction = EAST;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

std::map<GoodsId, std::string> goodsIdWithDescription
{
    {CANNON, "Basic Cannon"},
    {BOMB, "Bombs"},
    {FIRST_AID_KIT, "First Aid Kit"}
};

bool Crate::giveABonusToAPlayer(Player& player, std::string &information)
{
    if (collision(player, *this, BoundsType::RADIUS, BoundsType::RADIUS))
    {
        packageContent = static_cast<GoodsId>(rand() % 3);
        int currentAmmo = 0;
        switch (packageContent)
        {
        case CANNON:
            currentAmmo = player.weapons[BASIC_CANNON]->getAmmo();
            player.weapons[BASIC_CANNON]->setAmmo(currentAmmo + 10);
            information = "Cannon + 10!";
            break;
        case BOMB:
            currentAmmo = player.weapons[BOMB_DROP]->getAmmo();
            player.weapons[BOMB_DROP]->setAmmo(currentAmmo + 10);
            information = "Bombs + 10!";
            break;
        case FIRST_AID_KIT:
            player.energy += 25;
            information = "Energy Up!";
            break;
        }
        isToRemove = true;
        return true;
    }
    else
    {
        return false;
    }
}