#include "Input.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>

using namespace std;

TEST(skip_arguments, returns_true_if_stream_has_enough_argument)
{
	{
		stringstream is("0 1 2");
		Input input(is);
		EXPECT_TRUE(input.SkipArguments<string>(1));
	}
	{
		stringstream is("0 1 2");
		Input input(is);
		EXPECT_TRUE(input.SkipArguments<string>(2));
	}
	{
		stringstream is("0 1 2");
		Input input(is);
		EXPECT_TRUE(input.SkipArguments<string>(3));
	}
}

TEST(skip_arguments, returns_false_if_stream_has_not_enough_argument)
{
	stringstream is("0 1 2");
	Input input(is);
	EXPECT_FALSE(input.SkipArguments<string>(4));
}

TEST(skip_arguments, skips_argument)
{
	stringstream is("0 0.1 stringArgument");
	Input input(is);
	EXPECT_TRUE(input.SkipArguments<string>(2));

	string lastArgument;
	EXPECT_TRUE(input.ReadArguments(lastArgument));
	EXPECT_EQ(lastArgument, "stringArgument");
}

TEST(skip_arguments, does_not_skips_end_of_line)
{
	stringstream is("\n0 0.1 stringArgument");
	Input input(is);
	EXPECT_FALSE(input.SkipArguments<string>(2));

	string lastArgument;
	EXPECT_FALSE(input.ReadArguments(lastArgument));
	EXPECT_NE(lastArgument, "stringArgument");
}
