#pragma once

struct Line
{
	int Acoef;
	int Bcoef;
	int Ccoef;
};

struct Point
{
	int PosX;
	int PosY;
};

struct Round
{
	Point center;
	int radius;
};

int distanceFromPointToLine(Line line, Point point);
bool isRoundAndLineIntersecting(Line line, Round round);