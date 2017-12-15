#pragma once

#include "GameObject.h"
#include "weapon.h"

class Player : public GameObject
{
public:
    static const float ds; // unit displacement

	bool bulletReady;
	int reloadingPhase;
	bool shotFired;
	bool prevShotFired;
	bool addBullet;
	Weapon* weapon;

    Player();
	Player(float x, float y);
    Player(float x, float y, float collisionRadius, MyTexture& texture);

    ~Player();

    void moveObj(Direction direction);
};