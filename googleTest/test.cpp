#include "pch.h"
#include "../untitled-sdl-tank-game/utils/utils.cpp"

TEST(UtilsTestSuite, distanceFromPointToLineBasicTest) 
{
	Point point{ 0, 0 };
	Line line{ 1, 1, 0 };
	double distance = distanceFromPointToLine(line, point);
	EXPECT_EQ(0, distance );
}