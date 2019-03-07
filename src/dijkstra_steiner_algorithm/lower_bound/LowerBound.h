#ifndef CHIP_DESIGN_LOWERBOUND_H
#define CHIP_DESIGN_LOWERBOUND_H

#include "../../TerminalSubset.h"
#include "../../graph/HananGridGraph.h"

namespace dijkstra_steiner_algorithm {

namespace lower_bound {

class LowerBound
{
public:
	virtual Coord lower_bound(graph::Node const& v, TerminalSubset const& I) = 0;
};

}

}


#endif //CHIP_DESIGN_LOWERBOUND_H
