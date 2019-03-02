#include "pch.h"
#include "math.h"
#include "utils/utils.h"
#include "gtest/gtest.h"

TEST(UtilsTestSuite, distanceFromPointToLineBasicCaseTest1) 
{
	Point point{ 0, 0 };
	Line line{ 1, 1, 0 };
	EXPECT_EQ(0, distanceFromPointToLine(point, line));
}

TEST(UtilsTestSuite, distanceFromPointToLineBasicCaseTest2)
{
	Point point{ 0, 0 };
	Line line{ 1, 1, 4 };
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

TEST(UtilsTestSuite, distanceFromPointToLineHorizontalLineTest2)
{
	Point point{ 0, 0 };
	Line line{ 1, 0, -4 };
	EXPECT_EQ(4, distanceFromPointToLine(point, line));
}