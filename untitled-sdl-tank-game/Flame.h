#pragma once

#include "GameObject.h"

class Flame : public GameObject {
public:
	int texFrame;
	int lifeCycle;

	Flame();
	Flame(float x, float y);

	void act();
};