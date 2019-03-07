#include <boost/test/unit_test.hpp>
#include "../../fixtures/general_fixtures.h"
#include "../../../src/dijkstra_steiner_algorithm/lower_bound/MinimumSpanningTreeLowerBound.h"

using namespace dijkstra_steiner_algorithm::lower_bound;

struct MinimumSpanningTreeLowerBoundFixture : public GraphFixture{
	MinimumSpanningTreeLowerBound minimum_spanning_tree_lower_bound = {terminals};
};

BOOST_FIXTURE_TEST_CASE(TestMinimumSpanningTreeLowerBound_singleton, MinimumSpanningTreeLowerBoundFixture){
	BOOST_TEST(0 / 2 == minimum_spanning_tree_lower_bound.lower_bound(G.create_node(positions.at(0)), singleton_1));
}

BOOST_FIXTURE_TEST_CASE(TestMinimumSpanningTreeLowerBound_mid, MinimumSpanningTreeLowerBoundFixture){
	BOOST_TEST(6 / 2 == minimum_spanning_tree_lower_bound.lower_bound(G.create_node(positions.at(0)), full));
}