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


	Player(int x, int y);

	void handleGun();

};