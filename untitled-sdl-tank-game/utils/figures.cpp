#pragma once
#include "figures.h"

std::ostream& operator<<(std::ostream& out, Line line)
{
	out << "A = " << line.Acoef << " , B = " << line.Bcoef << ", c = " << line.Ccoef;
	return out;
}

std::ostream & operator<<(std::ostream & out, Point point)
{
	out << "PosX = " << point.PosX << ", PosY = " << point.PosY; 
	return out;
}

std::ostream & operator<<(std::ostream & out, Round round)
{
	out << "Center point = (" << round.center << " ) , radius = " << round.radius;
	return out;
}

