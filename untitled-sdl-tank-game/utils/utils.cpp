#include "utils.h"
#include "figures.h"
#include <math.h>
#include <tuple> 

int distanceFromPointToLine(Line line, Point point)
{
	return (line.Acoef * point.PosX + line.Bcoef * point.PosY + line.Ccoef) /
		sqrt( pow(line.Acoef, 2) + pow(line.Bcoef, 2) );
}

bool isRoundAndLineIntersecting(Line line, Round round)
{
	if(distanceFromPointToLine(line, round.center) > round.radius)
		return false;
	else
		return true;
}

double coutDelta(double a, double b, double c)
{
	// a*(x^2) + bx + c = 0
	if( a != 0 && c != 0 )
		return pow(b , 2) - 4 * a * c;
}

std::tuple<double, double> countSolutions(double a, double b, double c, double delta)
{
	if( a != 0 )
		return std::make_tuple<double, double> ( (pow(b, 2) - sqrt(delta)) / (2 * a), ((pow(b, 2) + sqrt(delta)) / (2 * a)) );
}