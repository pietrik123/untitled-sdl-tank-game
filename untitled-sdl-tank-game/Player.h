#pragma once

#include "GameObject.h"

class Player : public GameObject {
public:
	bool bulletReady;
	int reloadingPhase;
	bool shotFired;
	bool prevShotFired;
	bool addBullet;

	Player(int x, int y);

	void handleGun();

};