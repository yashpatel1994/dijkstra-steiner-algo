#ifndef CHIP_DESIGN_BOUNDINGBOXLOWERBOUND_H
#define CHIP_DESIGN_BOUNDINGBOXLOWERBOUND_H

#include "LowerBound.h"

namespace dijkstra_steiner_algorithm {

namespace lower_bound {

class BoundingBoxLowerBound : public LowerBound
{
public:
	BoundingBoxLowerBound(Terminal::Vector const &terminals) : terminals(terminals)
	{}

	Coord lower_bound(graph::Node const &v, TerminalSubset const &I) override
	{
		Coord sum = 0;
		for (auto const &dimension : DIMENSIONS) {
			Coord max = v.get_position().coord(dimension);
			Coord min = max;
			for (auto const &terminal : terminals) {
				if (I.contains(terminal)) {
					max = std::max(max, terminal.get_position().coord(dimension));
					min = std::min(min, terminal.get_position().coord(dimension));
				}
			}
			sum += max - min;
		}
		return sum;
	}

private:
	Terminal::Vector const &terminals;
};

}

}


#endif //CHIP_DESIGN_BOUNDINGBOXLOWERBOUND_H
