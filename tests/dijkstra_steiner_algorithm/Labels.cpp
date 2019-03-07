#include <boost/test/unit_test.hpp>
#include "../../src/dijkstra_steiner_algorithm/Labels.h"
#include "../../src/dijkstra_steiner_algorithm/DijkstraSteinerAlgorithm.h"

using namespace dijkstra_steiner_algorithm;

struct LabelsFixture
{
	LabelsFixture()
	{
		for (auto const x : {0, 1, 2, 3}) {
			for (auto const y : {0, 1, 2, 3}) {
				for (auto const z : {0, 1, 2, 3}) {
					nodes.push_back(graph.create_node({x, y, z}));
				}
			}
		}
	}

	Terminal::Vector terminals = {
			{{0, 0, 0}, 0},
			{{1, 1, 1}, 1},
			{{2, 2, 2}, 2},
			{{3, 3, 3}, 3}
	};
	Instance const instance = Instance::create(terminals);
	Labels labels = {instance};
	graph::HananGridGraph const &graph = instance.graph;
	std::vector<graph::Node> nodes;
};

BOOST_FIXTURE_TEST_CASE(TestLabels_permanently_labeled, LabelsFixture)
{
	auto const full_subset = TerminalSubset::create_full(terminals);
	auto const node1 = nodes.front();
	auto const node2 = nodes.back();

	BOOST_TEST(not labels.is_permanently_labeled({node1, full_subset}));
	BOOST_TEST(not labels.is_permanently_labeled({node2, full_subset}));
	labels.mark_permanently_labeled({node1, full_subset});
	BOOST_TEST(labels.is_permanently_labeled({node1, full_subset}));
	BOOST_TEST(not labels.is_permanently_labeled({node2, full_subset}));
	BOOST_TEST(std::set<TerminalSubset>{full_subset} == labels.get_permanently_labeled_subsets_for_node(node1));
	BOOST_TEST(std::set<TerminalSubset>{} == labels.get_permanently_labeled_subsets_for_node(node2));
	labels.mark_permanently_labeled({node2, full_subset});
	BOOST_TEST(labels.is_permanently_labeled({node1, full_subset}));
	BOOST_TEST(labels.is_permanently_labeled({node2, full_subset}));
}

BOOST_FIXTURE_TEST_CASE(TestLabels_get_set, LabelsFixture)
{
	auto const full_subset = TerminalSubset::create_full(terminals);
	auto const node1 = nodes.front();
	auto const node2 = nodes.back();

	BOOST_TEST(100000 < labels.get({node1, full_subset}));
	BOOST_TEST(100000 < labels.get({node2, full_subset}));
	labels.set({node1, full_subset}, 1);
	labels.set({node2, full_subset}, 2);
	BOOST_TEST(1 == labels.get({node1, full_subset}));
	BOOST_TEST(2 == labels.get({node2, full_subset}));
}