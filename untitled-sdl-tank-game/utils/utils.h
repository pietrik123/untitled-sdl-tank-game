#pragma once
#include "figures.h"
#include <vector>

double distanceFromPointToLine(Line line, Point point);
bool isRoundAndLineIntersecting(Line line, Circle circle);
double getDeleta(double a, double b, double c);
std::vector<double> countSolutions(double a, double b, double c, double delta);

// for Circle-Circle collison check
double distanceFromPointToPoint(Point firstPoint, Point secondPoint);
bool areRoundsIntersecting(Circle firstCircle, Circle secondCircle);

// for Rentangle-Rentangle collision check
bool isPointInRectangle(Point point, Rectangle rectangle);
bool areRectanglesIntersecting(Rectangle firstRectangle, Rectangle secondRectangle);
