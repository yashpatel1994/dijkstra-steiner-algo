#include <boost/test/unit_test.hpp>
#include "../../src/graph/HananGridGraph.h"
#include "../../src/utils.h"

using namespace graph;

struct SimpleGrid
{
	SimpleGrid() :
			graph({{1, 1, 1},
				   {2, 2, 2},
				   {3, 3, 3}})
	{}

	HananGridGraph graph;
};

BOOST_AUTO_TEST_CASE(TestHananGridNodeIndices)
{
	HananGridGraph graph({{1, 1, 1},
						  {2, 2, 2},
						  {3, 3, 3},
						  {4, 4, 4}});

	std::vector<graph::Node> nodes;
	for(auto const x : {1,2,3,4}){
		for(auto const y : {1,2,3,4}){
			for(auto const z : {1,2,3,4}){
				nodes.push_back(graph.create_node({x,y,z}));
			}
		}
	}

	std::set<size_t> indices;
	size_t max_index = 0;
	for(auto const& node : nodes){
		BOOST_TEST(0 == indices.count(graph.get_index(node)),  "Node index must be unique.");
		indices.insert(graph.get_index(node));
		max_index = std::max(max_index, graph.get_index(node));
	}
	BOOST_TEST(nodes.size() == graph.num_nodes());
	BOOST_TEST(max_index <= nodes.size());
}

BOOST_FIXTURE_TEST_CASE(TestHananGridNodeEquality, SimpleGrid)
{
	auto const a_1 = graph.create_node({2, 2, 2});
	auto const a_2 = graph.create_node({2, 2, 2});
	auto const b = graph.create_node({1, 1, 1});
	BOOST_CHECK(not (a_1 == b));
	BOOST_CHECK(not (b == a_1));
	BOOST_CHECK(a_1 == a_1);
	BOOST_CHECK(a_1 == a_2);
	BOOST_CHECK(b == b);
}

BOOST_FIXTURE_TEST_CASE(TestHananGridNeighbors1, SimpleGrid)
{
	auto const center = graph.create_node({2, 2, 2});
	BOOST_TEST(6 == graph.neighbors(center).size());
}

BOOST_FIXTURE_TEST_CASE(TestHananGridNeighbors2, SimpleGrid)
{
	auto const corner = graph.create_node({1, 1, 1});
	BOOST_TEST(3 == graph.neighbors(corner).size());
}

BOOST_FIXTURE_TEST_CASE(TestHananGridNeighbors3, SimpleGrid)
{
	auto const center = graph.create_node({2, 2, 2});
	auto const neighbors = graph.neighbors(center);
	std::vector<Position> expected_neighbors_positions = {
			{1, 2, 2},
			{3, 2, 2},
			{2, 1, 2},
			{2, 3, 2},
			{2, 2, 1},
			{2, 2, 3},
	};
	auto const actual_neighbors_positions
			= transform<Position>(neighbors, [](Node const &node) { return node.get_position(); });
	BOOST_TEST(expected_neighbors_positions == actual_neighbors_positions);
}