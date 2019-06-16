#include "Crate.h"
#include "GameObject.h"
#include "Player.h"

#include <random>

Crate::Crate()
{
    packageContent = static_cast<GoodsId>(rand() % 3);
}

void Crate::giveABonusToAPlayer(Player& player)
{
    if (collision(player, *this, BoundsType::RADIUS, BoundsType::RADIUS))
    {
        switch (packageContent)
        {
        case CANNON:
            int currentAmmo = player.weapons[BASIC_CANNON]->getAmmo();
            player.weapons[BASIC_CANNON]->setAmmo(currentAmmo + 10);
            break;
        case BOMB:
            int currentAmmo = player.weapons[BOMB_DROP]->getAmmo();
            player.weapons[BOMB_DROP]->setAmmo(currentAmmo + 10);
            break;
        case FIRST_AID_KIT:
            // TODO player.energy += 25
            break;
        }
    }
}