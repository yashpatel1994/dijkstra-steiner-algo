#ifndef CHIP_DESIGN_NODEPLUSTERMINALSUBSET_H
#define CHIP_DESIGN_NODEPLUSTERMINALSUBSET_H

namespace dijkstra_steiner_algorithm {

class NodePlusTerminalSubset
{
public:
	bool operator<(NodePlusTerminalSubset const &rhs) const
	{
		return std::tie(node, subset) < std::tie(rhs.node, rhs.subset);
	}

	graph::Node const node;
	TerminalSubset const subset;
};

}

#endif //CHIP_DESIGN_NODEPLUSTERMINALSUBSET_H
