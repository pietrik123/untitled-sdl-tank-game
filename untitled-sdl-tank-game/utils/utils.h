#pragma once
#include "figures.h"
#include <vector>

double distanceFromPointToLine(Point point, Line line);
bool areLineAndCircleIntersecting(Line line, Circle circle);
double getDelta(double a, double b, double c);
std::vector<double> countSolutions(double a, double b, double c, double delta);

// for Circle-Circle collison check
double distanceFromPointToPoint(Point firstPoint, Point secondPoint);
bool areCirclesIntersecting(Circle firstCircle, Circle secondCircle);

// for Rentangle-Rentangle collision check
bool isPointInRectangle(Point point, Rectangle rectangle);
bool areRectanglesIntersecting(Rectangle firstRectangle, Rectangle secondRectangle);
