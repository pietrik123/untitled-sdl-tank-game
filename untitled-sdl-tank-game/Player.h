#pragma once

#include "GameObject.h"
#include "weapon.h"

class Player : public GameObject
{
private:
    void basicInit();
public:
    float displcmt; // unit displacement

    bool bulletReady;
    int reloadingPhase;
    bool shotFired;
    bool prevShotFired;
    bool addBullet;
    Weapon* weapon;
    std::vector<Weapon*> weapons;
    int coinsCollected;

    unsigned int weaponIndex;

    Player();
    Player(float x, float y);
    Player(float x, float y, float collisionRadius, MyTexture* texture);

    Weapon* getCurrentWeapon();

    unsigned int energy;
    unsigned int maxEnergy;

    ~Player();

    void moveObj(Direction direction);
};