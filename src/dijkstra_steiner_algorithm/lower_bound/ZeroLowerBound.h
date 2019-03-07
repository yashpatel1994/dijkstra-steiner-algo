#ifndef CHIP_DESIGN_ZEROLOWERBOUND_H
#define CHIP_DESIGN_ZEROLOWERBOUND_H

#include "LowerBound.h"

namespace dijkstra_steiner_algorithm {

namespace lower_bound {

class ZeroLowerBound : public LowerBound
{
public:
	Coord lower_bound(graph::Node const &, TerminalSubset const &) override
	{
		return 0;
	}
};

}

}

#endif //CHIP_DESIGN_ZEROLOWERBOUND_H
