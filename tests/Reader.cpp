#include <boost/test/unit_test.hpp>
#include "../src/Reader.h"

BOOST_AUTO_TEST_CASE(TestReaderBadInput1){
	Reader reader;
	std::istringstream input("3\n1 2 3\n4 5 6 \n7 8 9 10\n");
	std::vector<Terminal> terminals;
	BOOST_CHECK_THROW(terminals = reader.read(input), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(TestReaderBadInput2){
	Reader reader;
	std::istringstream input("4\n1 2 3\n4 5 6 \n7 8 9\n");
	std::vector<Terminal> terminals;
	BOOST_CHECK_THROW(terminals = reader.read(input), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(TestReaderBadInput3){
	Reader reader;
	std::istringstream input("2\n1 2 3\n4 5 6 \n7 8 9\n");
	std::vector<Terminal> terminals;
	BOOST_CHECK_THROW(terminals = reader.read(input), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(TestReaderGoodInput){
	Reader reader;
	std::istringstream input("3\n1 2 3\n4 5 6 \n7 8 9\n");
	std::vector<Terminal> terminals;
	BOOST_CHECK_NO_THROW(terminals = reader.read(input));
	std::vector<Terminal> const expected_terminals = {{{1,2,3}, 0},{{4,5,6}, 1},{{7,8,9}, 2}};
	BOOST_TEST(terminals == expected_terminals);
}

