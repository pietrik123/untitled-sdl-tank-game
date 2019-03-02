#include "pch.h"
#include "../untitled-sdl-tank-game/utils/utils.cpp"
#include "math.h"

TEST(UtilsTestSuite, distanceFromPointToLineBasicCaseTest1) 
{
	Point point{ 0, 0 };
	Line line{ 1, 1, 0 };
	EXPECT_EQ(0, distanceFromPointToLine(point, line));
}

TEST(UtilsTestSuite, distanceFromPointToLineBasicCaseTest2)
{
	Point point{ 0, 0 };
	Line line{ 1, 1, -4 };
	EXPECT_EQ( roundf( sqrt(2) * 2 * 100 ) / 100, roundf( distanceFromPointToLine(point, line) * 100 ) / 100 );
}

TEST(UtilsTestSuite, distanceFromPointToLineVerticalLineTest)
{
	Point point{ 0, 0 };
	Line line{ 0, 1, -4 };
	EXPECT_EQ(4, distanceFromPointToLine(point, line));
}

TEST(UtilsTestSuite, distanceFromPointToLineHorizontalLineTest)
{
	Point point{ 0, 0 };
	Line line{ 1, 0, -4 };
	EXPECT_EQ(4, distanceFromPointToLine(point, line));
}

TEST(UtilsTestSuite, LineCoefficentsDoNotRepresentLine)
{
	bool wasExceptionCaught = false;

	try
	{
		Line line{ 0, 0, -4 };
	}
	catch(std::invalid_argument)
	{
		wasExceptionCaught = true;
	}

	EXPECT_EQ(true, wasExceptionCaught);
}

TEST(UtilsTestSuite, areLineAndCircleIntersectingTwoPointsOfIntersection)
{
	Circle circle{ { 0, 0 }, 1 };
	Line line{ 1, -1, 0 };
	EXPECT_EQ(true, areLineAndCircleIntersecting(line, circle));
}

TEST(UtilsTestSuite, areLineAndCircleIntersectingOnePointOfIntersection)
{
	Circle circle{ { 0, 0 }, 1 };
	Line line{ 1, 0, 1 };
	EXPECT_EQ(true, areLineAndCircleIntersecting(line, circle));
}

TEST(UtilsTestSuite, areLineAndCircleIntersectingNoIntersection)
{
	Circle circle{ { 0, 0 }, 1 };
	Line line{ 1, 0, 2 };
	EXPECT_EQ(false, areLineAndCircleIntersecting(line, circle));
}

TEST(UtilsTestSuite, getDeltaPositive)
{
	int a = 0; int b = 2; int c = 0;
	EXPECT_EQ(4, getDelta(a, b, c));
}

TEST(UtilsTestSuite, getDeltaZero)
{
	int a = 1; int b = 2; int c = 1;
	EXPECT_EQ(0, getDelta(a, b, c));
}

TEST(UtilsTestSuite, getDeltaNegative)
{
	int a = 5; int b = 2; int c = 5;
	EXPECT_EQ(-96, getDelta(a, b, c));
}

TEST(UtilsTestSuite, distanceFromPointToPointZeroDistance)
{
	Point point{ 0, 0 };
	EXPECT_EQ(0, distanceFromPointToPoint(point, point));
}

TEST(UtilsTestSuite, distanceFromPointToPointTwoPointsOnVerticalLine)
{
	Point pointOne{ 0, 0 };
	Point pointTwo{ 5, 0 };
	EXPECT_EQ(5, distanceFromPointToPoint(pointOne, pointTwo));
}

TEST(UtilsTestSuite, distanceFromPointToPointTwoPointsOnHorizontalLine)
{
	Point pointOne{ 0, 0 };
	Point pointTwo{ 0, 5 };
	EXPECT_EQ(5, distanceFromPointToPoint(pointOne, pointTwo));
}

TEST(UtilsTestSuite, distanceFromPointToPoint)
{
	Point pointOne{ 0, 0 };
	Point pointTwo{ 5, 5 };
	EXPECT_EQ(sqrt(2) * 5, distanceFromPointToPoint(pointOne, pointTwo));
}
