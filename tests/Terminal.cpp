#include <boost/test/unit_test.hpp>
#include "../src/Terminal.h"


BOOST_AUTO_TEST_CASE(TestTerminalPosition)
{
	Position const position = {1,2,3};
	BOOST_CHECK(position == Terminal(position, 0).get_position());
}

BOOST_AUTO_TEST_CASE(TestTerminalIndex)
{
	Terminal::Index const index = 3;
	BOOST_CHECK(index == Terminal({1,2,3}, index).get_index());
}

BOOST_AUTO_TEST_CASE(TestTerminalEquality)
{
	Terminal const terminal({1,2,3}, 0);
	BOOST_CHECK(terminal == terminal);
}

BOOST_AUTO_TEST_CASE(TestTerminalInequality)
{
	Terminal const terminal1({1,2,3}, 0);
	Terminal const terminal2({1,2,4}, 1);
	BOOST_CHECK(terminal1 != terminal2);
}