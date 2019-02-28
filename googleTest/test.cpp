#include "pch.h"
#include "../untitled-sdl-tank-game/utils/utils.cpp"
#include "math.h"

TEST(UtilsTestSuite, distanceFromPointToLineBasicTest) 
{
	Point point{ 0, 0 };
	Line line{ 1, 1, 0 };
	EXPECT_EQ(0, distanceFromPointToLine(line, point));
}

TEST(UtilsTestSuite, distanceFromPointToLineBasicTestTwo)
{
	Point point{ 0, 0 };
	Line line{ 1, 1, 4 };
	EXPECT_EQ( roundf( sqrt(2) * 2 * 100 ) / 100, roundf( distanceFromPointToLine( line, point ) * 100 ) / 100 );
}