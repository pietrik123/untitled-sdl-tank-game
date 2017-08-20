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
	virtual void act() {}
	virtual bool trigger() { return false; }
};

//basic cannon class

class BasicCannon : public Weapon
{
public: 
	BasicCannon();
	static const int READY = 100;
	void act();
	bool trigger();
};


