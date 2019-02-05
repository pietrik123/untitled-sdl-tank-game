#include "utils.h"
#include "figures.h"
#include <math.h>
#include <tuple> 
#include <vector>

double distanceFromPointToLine(Line line, Point point)
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
	return pow(b , 2) - 4 * a * c;
}

std::tuple<double, double> countSolutions(double a, double b, double c, double delta)
{
	if (a != 0 && delta > 0)
		return std::make_tuple<double, double>((pow(b, 2) - sqrt(delta)) / (2 * a), ((pow(b, 2) + sqrt(delta)) / (2 * a)));
	else if (a != 0 && delta == 0)
		return std::make_tuple<double, double>((-b / (2 * a)), (-b / (2 * a)));
}

double distanceFromPointToPoint(Point firstPoint, Point secondPoint)
{
	return sqrt(pow(firstPoint.PosX - secondPoint.PosX, 2) - pow(firstPoint.PosY - secondPoint.PosY, 2));
}

bool areRoundsIntersecting(Round firstRound, Round secondRound)
{
	// one or two points of intersection
	if (distanceFromPointToPoint(firstRound.center, secondRound.center) <= firstRound.radius + secondRound.radius)
		return true;
	else
		return false;
}

bool isPointInRectangle(Point point, Rectangle rectangle)
{
	// does NOT apply to twisted ractangles
	if (point.PosX >= rectangle.bottomLeftCorner.PosX
		&& point.PosX <= rectangle.bottomRightCorner.PosX
		&& point.PosY >= rectangle.bottomLeftCorner.PosY
		&& point.PosY <= rectangle.topLeftCorner.PosY)
		return true;
	else
		return false;
}

bool areRectanglesIntersecting(Rectangle firstRectangle, Rectangle secondRectangle)
{
	// std::vector<Point> rect {firstRectangle.topLeftCorner, firstRectangle.topRightCorner, firstRectangle.bottomRightCorner, firstRectangle.bottomLeftCorner};
	// vector and for ... each better?
	if (isPointInRectangle(firstRectangle.topLeftCorner, secondRectangle)
		|| isPointInRectangle(firstRectangle.topRightCorner, secondRectangle)
		|| isPointInRectangle(firstRectangle.bottomRightCorner, secondRectangle)
		|| isPointInRectangle(firstRectangle.bottomLeftCorner, secondRectangle))
		return true;
	else
		return false;
}


