#include "weapon.h"

// this method is called when player pushes 'fire' button

// for now returns true if bullet is released 
// in the future the method may call something like that 'gameScene.addBullet()'
// or send some signal, which would add a bullet to a game scene
bool Weapon::trigger()
{
//#define INFINITE_AMMO
#ifndef INFINITE_AMMO
    if (ammo <= 0)
    {
        return false;
    }
#endif
    if (readyCnt >= READY)
    {
        readyCnt = 0;
        ammo--;
        return true;
    }
    return false;
}

// this method should be called every cycle of game main loop
void BasicCannon::act()
{
    if (readyCnt < READY)
    {
        readyCnt += 5;
    }
}

BasicCannon::BasicCannon()
{
    readyCnt = READY;
}

BombDrop::BombDrop()
{
    readyCnt = READY;
}

void BombDrop::act()
{
    if (readyCnt < READY)
    {
        readyCnt += 5;
    }
}

MachineGun::MachineGun()
{
    readyCnt = READY;
}

void MachineGun::act()
{
    if (readyCnt < READY)
    {
        readyCnt += 1;
    }
}

