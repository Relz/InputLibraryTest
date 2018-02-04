#include "../../Input/Input.h"
#include "gtest/gtest.h"
#include <sstream>

using namespace std;

const char SPACE_SYMBOL = ' ';
const char ENDL_SYMBOL = '\n';

TEST(skip_symbols_function, skips_single_symbol_and_returns_true_if_any_symbol_was_skipped)
{
	{
		std::string isString = "                       #";
		stringstream is(isString);
		CInput input(is);
		EXPECT_TRUE(input.SkipSymbols({ SPACE_SYMBOL }));
		EXPECT_EQ(is.peek(), char_traits<char>::to_int_type('#'));
		EXPECT_EQ(input.GetPosition().GetLine(), 1);
		EXPECT_EQ(input.GetPosition().GetColumn(), static_cast<long>(isString.length()));
	}
	{
		stringstream is("#");
		CInput input(is);
		EXPECT_FALSE(input.SkipSymbols({ SPACE_SYMBOL }));
		EXPECT_EQ(is.peek(), char_traits<char>::to_int_type('#'));
		EXPECT_EQ(input.GetPosition().GetLine(), 1);
		EXPECT_EQ(input.GetPosition().GetColumn(), 1);
	}
	{
		stringstream is("\n\n\n\n\n\n\n\n\n\n\n#");
		CInput input(is);
		EXPECT_TRUE(input.SkipSymbols({ ENDL_SYMBOL }));
		EXPECT_EQ(is.peek(), char_traits<char>::to_int_type('#'));
		EXPECT_EQ(input.GetPosition().GetLine(), 12);
		EXPECT_EQ(input.GetPosition().GetColumn(), 1);
	}
	{
		stringstream is("#");
		CInput input(is);
		EXPECT_FALSE(input.SkipSymbols({ ENDL_SYMBOL }));
		EXPECT_EQ(is.peek(), char_traits<char>::to_int_type('#'));
		EXPECT_EQ(input.GetPosition().GetLine(), 1);
		EXPECT_EQ(input.GetPosition().GetColumn(), 1);
	}
}

TEST(skip_symbols_function, skips_multiple_symbols)
{
	{
		stringstream is("  \n\n      \n\n\n\n\n   \n\n\n\n   #");
		CInput input(is);
		EXPECT_TRUE(input.SkipSymbols({ SPACE_SYMBOL, ENDL_SYMBOL }));
		EXPECT_EQ(is.peek(), char_traits<char>::to_int_type('#'));
		EXPECT_EQ(input.GetPosition().GetLine(), 12);
		EXPECT_EQ(input.GetPosition().GetColumn(), 4);
	}
	{
		stringstream is("#");
		CInput input(is);
		EXPECT_FALSE(input.SkipSymbols({ SPACE_SYMBOL, ENDL_SYMBOL }));
		EXPECT_EQ(is.peek(), char_traits<char>::to_int_type('#'));
		EXPECT_EQ(input.GetPosition().GetLine(), 1);
		EXPECT_EQ(input.GetPosition().GetColumn(), 1);
	}
}
