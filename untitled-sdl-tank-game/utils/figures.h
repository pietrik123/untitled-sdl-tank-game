#pragma once
#include <iostream>
#include <exception>

struct Line
{
	double Acoef;
	double Bcoef;
	double Ccoef;

	Line(double Aco, double Bco, double Cco)
	{
		if (Aco == 0 && Bco == 0)
			throw std::invalid_argument("Line cannot have both A and B coefficents equal to 0!");
		else
		{
			Acoef = Aco;
			Bcoef = Bco;
			Ccoef = Cco;
		}
	}
	friend std::ostream& operator << (std::ostream& out, const Line line);
};

struct Point
{
	double PosX;
	double PosY;

	friend std::ostream& operator << (std::ostream& out, const Point point);
};

struct Circle
{
	Point center;
	double radius;

	friend std::ostream& operator << (std::ostream& out, const Circle circle);
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