#include "Flame.h"

#include <iostream>

Flame :: Flame() {}

Flame :: Flame(float x, float y) : GameObject(x, y)
{
	std::cout << "Flame created!" << std::endl;
	texFrame = 0;
	lifeCycle = 0;
}

Flame :: Flame(float x, float y, MyTexture& texture) : GameObject(x, y)
{
    std::cout << "Flame created!" << std::endl;
    texFrame = 0;
    lifeCycle = 0;
    myTex = texture;
}

void Flame :: act()
{
	lifeCycle += 1;

	if (lifeCycle % 3 == 0)
    {
		texFrame += 1;
	}
}
