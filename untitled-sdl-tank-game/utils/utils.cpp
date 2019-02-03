#include "utils.h"
#include "math.h"

int distanceFromPointToLine(Line line, Point point)
{
	int distance = (line.Acoef * point.PosX + line.Bcoef * point.PosY + line.Ccoef) /
		sqrt(pow(line.Acoef, 2) + pow(line.Bcoef, 2));
	return distance;
}

bool isRoundAndLineIntersecting(Line line, Round round)
{
	int lineToRoundCenterDistance = distanceFromPointToLine(line, round.center);
	if (lineToRoundCenterDistance > round.radius)
		return false;
	else
		return true;
}