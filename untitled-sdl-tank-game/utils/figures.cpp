#pragma once
#include "figures.h"

std::ostream& operator<<(std::ostream& out, const Line line)
{
	out << "A = " << line.Acoef << " , B = " << line.Bcoef << ", c = " << line.Ccoef;
	return out;
}

std::ostream & operator<<(std::ostream & out, const Point point)
{
	out << "PosX = " << point.PosX << ", PosY = " << point.PosY; 
	return out;
}

std::ostream & operator<<(std::ostream & out, const Circle round)
{
	out << "Center point = (" << round.center << " ) , radius = " << round.radius;
	return out;
}

std::ostream & operator<<(std::ostream & out, const Rectangle rectangle)
{
	out << "A---------B\n |       | \n |       | \n |       | \nC---------D\n A = "
			<< rectangle.topLeftCorner << ", B = " << rectangle.topRightCorner << ", C = " << rectangle.bottomLeftCorner
				<< ", D = " << rectangle.bottomRightCorner << ".\n";
	return out;
}

