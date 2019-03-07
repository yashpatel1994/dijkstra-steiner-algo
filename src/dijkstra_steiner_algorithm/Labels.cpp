#include "Labels.h"
#include "DijkstraSteinerAlgorithm.h"

namespace dijkstra_steiner_algorithm {

Labels::Labels(Instance const &instance) :
		graph(instance.graph),
		labels(graph.num_nodes()),
		permanently_labeled(graph.num_nodes())
{}

Coord Labels::get(NodePlusTerminalSubset const &node_plus_terminal_subset) const
{
	if (labels.at(graph.get_index(node_plus_terminal_subset.node)).count(node_plus_terminal_subset.subset)) {
		return labels.at(graph.get_index(node_plus_terminal_subset.node)).at(node_plus_terminal_subset.subset);
	} else {
		return std::numeric_limits<Coord>::max();
	}
}

void Labels::set(NodePlusTerminalSubset const &node_plus_terminal_subset, Coord const new_value)
{
	labels.at(graph.get_index(node_plus_terminal_subset.node))[node_plus_terminal_subset.subset] = new_value;
}

void Labels::mark_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset)
{
	assert(not is_permanently_labeled(node_plus_terminal_subset));
	permanently_labeled.at(graph.get_index(node_plus_terminal_subset.node)).insert(node_plus_terminal_subset.subset);
}

bool Labels::is_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset) const
{
	return 0 != (permanently_labeled
			.at(graph.get_index(node_plus_terminal_subset.node))
			.count(node_plus_terminal_subset.subset));
}

std::set<TerminalSubset> const &Labels::get_permanently_labeled_subsets_for_node(graph::Node const &node) const
{
	return permanently_labeled.at(graph.get_index(node));
}

}