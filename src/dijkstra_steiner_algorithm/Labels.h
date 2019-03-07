#ifndef CHIP_DESIGN_LABELS_H
#define CHIP_DESIGN_LABELS_H


#include <map>
#include "../graph/HananGridGraph.h"
#include "../TerminalSubset.h"
#include "NodePlusTerminalSubset.h"

namespace dijkstra_steiner_algorithm {

class Instance;

/**
 * Stores the labels used in the Dijkstra Steiner Algorithm.
 */
class Labels
{
public:
	Labels(Instance const &instance);

	/**
	 * Retrieve a label.
	 */
	Coord get(NodePlusTerminalSubset const &node_plus_terminal_subset) const;

	/**
	 * Create or update a label.
	 */
	void set(NodePlusTerminalSubset const &node_plus_terminal_subset, Coord const new_value);

	void mark_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset);

	bool is_permanently_labeled(NodePlusTerminalSubset const &node_plus_terminal_subset) const;

	std::set<TerminalSubset> const &get_permanently_labeled_subsets_for_node(graph::Node const &node) const;

private:
	graph::HananGridGraph const &graph;
	std::vector<std::map<TerminalSubset, Coord>> labels; // one map for every node
	std::vector<std::set<TerminalSubset>> permanently_labeled; // one set for every node
};

}


#endif //CHIP_DESIGN_LABELS_H
