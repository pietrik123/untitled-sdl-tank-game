#include "Player.h"

Player :: Player(int x, int y) : GameObject(x, y) {
	posX = x;
	posY = y;
	myTex = NULL;

	bulletReady = true;
	reloadingPhase = 100;
	shotFired = false;
	prevShotFired = false;
	addBullet = false;
}

void Player :: handleGun() {
	if (shotFired == true && prevShotFired == false && bulletReady == true) {
		bulletReady = false;
		reloadingPhase = 0;
		addBullet = true;
	}
	else {
		addBullet = false;
	}

	if (bulletReady == false) {
		if (reloadingPhase < 100) {
			reloadingPhase += 10;
		}
		if (reloadingPhase >= 100) {
			bulletReady = true;
		}
	}

	prevShotFired = shotFired;
}
