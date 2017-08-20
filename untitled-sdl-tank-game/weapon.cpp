#include "weapon.h"


// this method should be called every cycle of game main loop
void BasicCannon::act()
{
	if (readyCnt < READY)
	{
		readyCnt += 5;
	}
}


BasicCannon :: BasicCannon()
{
	readyCnt = 100;
}

// this method is called when player pushes 'fire' button

// for now returns true if bullet is released 
// in the future the method may call something like that 'gameScene.addBullet()'
// or send some signal, which would add a bullet to a game scene
bool BasicCannon::trigger()
{
	// if cannon is ready ...
	if (readyCnt >= READY)
	{
		// reset ready counter
		readyCnt = 0;
		return true;
	}

	return false;

	// TODO add bullet to the scene
}