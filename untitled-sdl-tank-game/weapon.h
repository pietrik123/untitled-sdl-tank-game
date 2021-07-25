#pragma once

//base class for all weapons
class Weapon
{
public:
    static const int READY = 100;
protected:
    int readyCnt = 0;
    int ammo = 0;
public:
    int getAmmo() { return ammo;  }
    void setAmmo(int ammoParam) { ammo = ammoParam;  }
    virtual void act() {}
    virtual bool trigger();
};

enum WeaponId
{
    BASIC_CANNON,
    BOMB_DROP
};

//basic cannon class

class BasicCannon : public Weapon
{
public: 
    BasicCannon();
    static const int READY = 100;
    void act();
};

class BombDrop : public Weapon
{
public:
    BombDrop();
    static const int READY = 200;
    void act();
};

class MachineGun : public Weapon
{
public:
    MachineGun();
    static const int READY = 5;
    void act();
};

