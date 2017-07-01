#pragma once

#include "GameObject.h"

class Flame : public GameObject {
public:
	int texFrame;
	int lifeCycle;

	Flame();
	Flame(int x, int y);

	void act();
};