#pragma once
#include "figures.h"

int distanceFromPointToLine(Line line, Point point);
bool isRoundAndLineIntersecting(Line line, Round round);
double coutDelta(double a, double b, double c);
std::tuple<double, double> countSolutions(double a, double b, double c, double delta);