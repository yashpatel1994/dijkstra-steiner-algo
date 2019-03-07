#ifndef CHIP_DESIGN_MINIMUMSPANNINGTREELOWERBOUND_H
#define CHIP_DESIGN_MINIMUMSPANNINGTREELOWERBOUND_H

#include "LowerBound.h"
#include "../../heap/Heap.h"

namespace dijkstra_steiner_algorithm {

namespace lower_bound {

class MinimumSpanningTreeLowerBound : public LowerBound
{
public:
	MinimumSpanningTreeLowerBound(Terminal::Vector const &terminals) :
			terminals(terminals),
			cache(pow2(terminals.size()), std::numeric_limits<Coord>::max())
	{}

	/**
	 * Calculates the length of a minimum spanning tree on I.
	 * Caches the result internally.
	 */
	Coord lower_bound(graph::Node const &/*v*/, TerminalSubset const &I) override
	{
		auto &cached_value = cache.at(I.get_index());
		if (cached_value == std::numeric_limits<Coord>::max()) {
			cached_value = calculate_minimum_spanning_tree_length(I);
		}
		return cached_value;
	}

private:

	Coord calculate_minimum_spanning_tree_length(TerminalSubset const &I) const
	{
		if (I.empty()) {
			return 0;
		}

		std::vector<Coord> distances(terminals.size(), std::numeric_limits<Coord>::max());

		Terminal const *first_terminal = nullptr;
		for (auto const &terminal : terminals) {
			if (I.contains(terminal)) {
				first_terminal = &terminal;
				break;
			}
		}
		assert(first_terminal != nullptr);

		for (auto const &terminal : terminals) {
			if (I.contains(terminal) and *first_terminal != terminal) {
				distances.at(terminal.get_index()) = first_terminal->get_position().distance(terminal.get_position());
			}
		}

		Coord total_length = 0;

		TerminalSubset terminals_in_tree = TerminalSubset::create_singleton(*first_terminal, terminals);

		while (not terminals_in_tree.contains(I)) {
			auto const &new_terminal = *std::min_element(
					terminals.begin(),
					terminals.end(),
					[&distances](Terminal const &lhs, Terminal const &rhs) {
						return distances.at(lhs.get_index()) < distances.at(rhs.get_index());
					}
			);

			total_length += distances.at(new_terminal.get_index());
			distances.at(new_terminal.get_index()) = std::numeric_limits<Coord>::max();

			terminals_in_tree.add(new_terminal);

			for (auto const &terminal : terminals) {
				if (I.contains(terminal) and not terminals_in_tree.contains(terminal)) {
					distances.at(terminal.get_index()) = std::min(
							distances.at(terminal.get_index()),
							new_terminal.get_position().distance(terminal.get_position())
					);
				}
			}
		}

		return total_length / 2;
	}

	Terminal::Vector const &terminals;
	std::vector<Coord> cache;
};

}

}

#endif //CHIP_DESIGN_MINIMUMSPANNINGTREELOWERBOUND_H
