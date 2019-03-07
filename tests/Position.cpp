#include <boost/test/unit_test.hpp>
#include "../src/Position.h"

BOOST_AUTO_TEST_CASE(TestPosition){
	Position a{1,1,1};
	Position b{2,2,2};
	BOOST_TEST(a.distance(b) == b.distance(a));
	BOOST_TEST(3 == b.distance(a));
}