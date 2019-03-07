#include <boost/test/unit_test.hpp>
#include "../src/utils.h"

BOOST_AUTO_TEST_CASE(createRange)
{
	std::vector<int> const expected = {0, 1, 2, 3, 4};
	auto const actual = create_0_to_n_minus_one(5);
	BOOST_TEST(expected == actual);
}

BOOST_AUTO_TEST_CASE(filter_test)
{
	auto const even = [](int i) { return (i % 2) == 0; };
	std::vector<int> const vector = {0, 1, 2, 3, 4};
	std::vector<int> const expected = {0, 2, 4};
	BOOST_TEST(expected == filter<int>(vector, even));
}

BOOST_AUTO_TEST_CASE(append_test)
{
	std::vector<int> vector_a = {0, 1, 2};
	std::vector<int> const vector_b = {3, 4};
	std::vector<int> const expected = {0, 1, 2, 3, 4};
	append(vector_a, vector_b);
	BOOST_TEST(expected == vector_a);
}

BOOST_AUTO_TEST_CASE(pow2_test)
{
	BOOST_TEST(1  == pow2(0));
	BOOST_TEST(2  == pow2(1));
	BOOST_TEST(4  == pow2(2));
	BOOST_TEST(8  == pow2(3));
}

