#pragma once
#include <iostream>

struct Line
{
	double Acoef;
	double Bcoef;
	double Ccoef;

	friend std::ostream& operator << (std::ostream& out, const Line line);
};

struct Point
{
	double PosX;
	double PosY;

	friend std::ostream& operator << (std::ostream& out, const Point point);
};

struct Round
{
	Point center;
	double radius;

	friend std::ostream& operator << (std::ostream& out, const Round round);
};

struct Rectangle
{
	// better represent as vector?
	Point topLeftCorner;
	Point topRightCorner;
	Point bottomLeftCorner;
	Point bottomRightCorner;

	friend std::ostream& operator << (std::ostream& out, const Rectangle rectangle);
};