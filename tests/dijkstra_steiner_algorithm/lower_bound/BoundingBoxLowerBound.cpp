#include <boost/test/unit_test.hpp>
#include "../../fixtures/general_fixtures.h"
#include "../../../src/dijkstra_steiner_algorithm/lower_bound/BoundingBoxLowerBound.h"

using namespace dijkstra_steiner_algorithm::lower_bound;

struct BoundingBoxLowerBoundFixture : public GraphFixture{
	BoundingBoxLowerBound bounding_box_lower_bound = {terminals};
};

BOOST_FIXTURE_TEST_CASE(TestBoundingBoxLowerBound_singleton, BoundingBoxLowerBoundFixture){
	BOOST_TEST(0 == bounding_box_lower_bound.lower_bound(G.create_node(positions.at(0)), empty));
}

BOOST_FIXTURE_TEST_CASE(TestBoundingBoxLowerBound_max, BoundingBoxLowerBoundFixture){
	BOOST_TEST(6 == bounding_box_lower_bound.lower_bound(G.create_node(positions.at(0)), singleton_2));
}

BOOST_FIXTURE_TEST_CASE(TestBoundingBoxLowerBound_mid, BoundingBoxLowerBoundFixture){
	BOOST_TEST(3 == bounding_box_lower_bound.lower_bound(G.create_node(positions.at(1)), singleton_2));
}