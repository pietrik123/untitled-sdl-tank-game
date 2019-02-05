#pragma once
#include "figures.h"

double distanceFromPointToLine(Line line, Point point);
bool isRoundAndLineIntersecting(Line line, Round round);
double coutDelta(double a, double b, double c);
std::tuple<double, double> countSolutions(double a, double b, double c, double delta);

// for Circle-Circle collison check
double distanceFromPointToPoint(Point firstPoint, Point secondPoint);
bool areRoundsIntersecting(Round firstRound, Round secondRound);

// for Rentangle-Rentangle collision check
bool isPointInRectangle(Point point, Rectangle rectangle);
bool areRectanglesIntersecting(Rectangle firstRectangle, Rectangle secondRectangle);
