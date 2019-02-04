#pragma once
#include <iostream>

struct Line
{
	int Acoef;
	int Bcoef;
	int Ccoef;

	friend std::ostream& operator << (std::ostream& out, Line line);
};

struct Point
{
	int PosX;
	int PosY;

	friend std::ostream& operator << (std::ostream& out, Point point);
};

struct Round
{
	Point center;
	int radius;

	friend std::ostream& operator << (std::ostream& out, Round round);
};
