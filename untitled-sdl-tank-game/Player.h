#pragma once

#include "GameObject.h"
#include "weapon.h"

class Player : public GameObject {
public:
	bool bulletReady;
	int reloadingPhase;
	bool shotFired;
	bool prevShotFired;
	bool addBullet;
	Weapon* weapon;


	Player(float x, float y);

	void handleGun();

};