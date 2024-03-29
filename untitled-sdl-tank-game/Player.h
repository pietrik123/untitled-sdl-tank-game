#pragma once

#include "GameObject.h"
#include "weapon.h"

class Player : public GameObject
{
private:
    void basicInit();
public:
    // player speed, unit: [game distance unit]/[1*frame]
    float speed;

    bool bulletReady;
    int reloadingPhase;
    bool shotFired;
    bool prevShotFired;
    bool addBullet;
    Weapon* weapon;
    std::vector<Weapon*> weapons;
    int coinsCollected;

    Direction basicCannonShootingDirection;
    float machineGunShootingAngle;

    unsigned int weaponIndex;
    
    // Counts ticks after player is hit by enemy.
    // Used so that player does not lose energy each time tick,
    // when collision with an enemy is detected.
    // Player should lose energy only on the first tick.
    unsigned int afterHitCounter;

    Player();
    Player(float x, float y);
    Player(float x, float y, float collisionRadius, MyTexture* texture);

    Weapon* getCurrentWeapon() const;

    unsigned int energy;
    unsigned int maxEnergy;

    ~Player();

    void act();
    void moveObj(Direction direction);
};