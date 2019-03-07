#ifndef CHIP_DESIGN_INSTANCE_H
#define CHIP_DESIGN_INSTANCE_H

#include "../Terminal.h"
#include "../graph/HananGridGraph.h"

namespace dijkstra_steiner_algorithm {

class Instance
{
public:
	static Instance create(Terminal::Vector const &terminals)
	{
		Position::Vector positions;
		for (auto const &terminal:terminals) {
			positions.push_back(terminal.get_position());
		}
		return {graph::HananGridGraph{positions}, terminals, terminals.front()};
	}

	graph::HananGridGraph const graph;
	Terminal::Vector const &terminals; // contains t
	Terminal const &t;
};

}


#endif //CHIP_DESIGN_INSTANCE_H
