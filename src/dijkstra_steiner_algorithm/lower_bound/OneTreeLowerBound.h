#ifndef CHIP_DESIGN_ONETREELOWERBOUND_H
#define CHIP_DESIGN_ONETREELOWERBOUND_H

#include "LowerBound.h"
#include "MinimumSpanningTreeLowerBound.h"

namespace dijkstra_steiner_algorithm {

namespace lower_bound {

class OneTreeLowerBound : public LowerBound
{
public:
	OneTreeLowerBound(Terminal::Vector const &terminals) :
			minimum_spanning_tree_lower_bound(terminals),
			terminals(terminals)
	{}

	Coord lower_bound(graph::Node const &v, TerminalSubset const &I) override
	{
		if (I.empty()) {
			return 0;
		}

		auto const minimum_spanning_tree_length = minimum_spanning_tree_lower_bound.lower_bound(v, I);

		auto const v_position = v.get_position();

		Coord min = std::numeric_limits<Coord>::max();
		Coord second_min = std::numeric_limits<Coord>::max();

		for (size_t i = 0; i < terminals.size(); i++) {
			auto const &terminal = terminals[i];
			if (I.contains(terminal)) {
				auto const distance = v_position.distance(terminal.get_position());
				if (distance < min) {
					second_min = min;
					min = distance;
				} else if (distance < second_min) {
					second_min = distance;
				}
			}
		}

		if (I.is_singleton()) {
			return minimum_spanning_tree_length + min;
		} else {
			return minimum_spanning_tree_length + (min + second_min) / 2;
		}
	}

private:
	MinimumSpanningTreeLowerBound minimum_spanning_tree_lower_bound;
	Terminal::Vector const &terminals;
};

}

}


#endif //CHIP_DESIGN_ONETREELOWERBOUND_H
