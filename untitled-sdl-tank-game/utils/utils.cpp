#include "utils.h"
#include "figures.h"
#include <math.h> 
#include <vector>

double distanceFromPointToLine(Point point, Line line)
{
	// Acoef == Bcoef == 0 case secured in Line constructor
	return abs( (line.Acoef * point.PosX + line.Bcoef * point.PosY + line.Ccoef) /
		sqrt( pow(line.Acoef, 2) + pow(line.Bcoef, 2) ) );
}

bool areLineAndCircleIntersecting(Line line, Circle circle)
{
	if(distanceFromPointToLine(circle.center, line) > circle.radius)
		return false;
	else
		return true;
}

double getDelta(double a, double b, double c)
{
	// a*(x^2) + bx + c = 0
	return pow(b , 2) - 4 * a * c;
}

std::vector<double> countSolutions(double a, double b, double c, double delta)
{
	// function returns vector which size depends on number of solutions. This can also be empty vector, so checking is required outside of function
	if (a != 0 && delta > 0)
		return std::vector<double>{(pow(b, 2) - sqrt(delta)) / (2 * a), ((pow(b, 2) + sqrt(delta)) / (2 * a))};
	else if (a != 0 && delta == 0)
		return std::vector<double>{-b / (2 * a)};
	else
		return std::vector<double>{};
}


double distanceFromPointToPoint(Point firstPoint, Point secondPoint)
{
	return sqrt(pow(firstPoint.PosX - secondPoint.PosX, 2) + pow(firstPoint.PosY - secondPoint.PosY, 2));
}

bool areCirclesIntersecting(Circle firstCircle, Circle secondCircle)
{
	// one or two points of intersection
	if (distanceFromPointToPoint(firstCircle.center, secondCircle.center) <= firstCircle.radius + secondCircle.radius)
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