#include "Player.h"
#include "game_settings.h"

void Player::basicInit()
{
    energy = PLAYER_MAX_ENERGY;
    maxEnergy = PLAYER_MAX_ENERGY;
    bulletReady = true;
    reloadingPhase = 100;
    shotFired = false;
    prevShotFired = false;
    addBullet = false;
    speed = PLAYER_SPEED;
    coinsCollected = 0;
    afterHitCounter = 0;
    basicCannonShootingDirection = EAST;

    weaponIndex = WeaponId::BASIC_CANNON;
    weapons.push_back(new BasicCannon());
    weapons.push_back(new BombDrop());
}

Player::Player()
{
    basicInit();
}

Player::Player(float x, float y) : GameObject(x, y)
{
    basicInit();
}

Player::Player(float x, float y, float collisionRadius, MyTexture* texture)
    : GameObject(x, y, collisionRadius, texture)
{
    basicInit();
    weapons[WeaponId::BASIC_CANNON]->setAmmo(10);
    weapons[WeaponId::BOMB_DROP]->setAmmo(10);

    coinsCollected = 0;
}

Player::~Player()
{
    
}

void Player::moveObj(Direction direction)
{
    if (direction == WEST)
    {
        posX -= speed;
    }
    if (direction == EAST)
    {
        posX += speed;
    }
    if (direction == NORTH)
    {
        posY += speed;
    }
    if (direction == SOUTH)
    {
        posY -= speed;
    }
}

void Player::act()
{
    if (energy > maxEnergy)
    {
        energy = maxEnergy;
    }

    // handle hits by enemies - player loses energy
    // lose energy only on the 1st tick
    if (afterHitCounter == 1)
    {
        if (static_cast<int>(energy - 10) < 0)
        {
            energy = 0;
        }
        else
        {
            energy -= 10;
        }
    }
    // inc. counter
    if (afterHitCounter > 0 && afterHitCounter < 100)
    {
        afterHitCounter += 1;
    }
    // overflow - reset counter
    if (afterHitCounter >= 100)
    {
        afterHitCounter = 0;
    }
}

Weapon* Player::getCurrentWeapon()
{
    return weapons[weaponIndex];
}