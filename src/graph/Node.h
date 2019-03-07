#ifndef CHIP_DESIGN_NODE_H
#define CHIP_DESIGN_NODE_H

#include <vector>
#include "../typedefs.h"
#include "../Position.h"

namespace graph {

class Node
{
public:
	Node(std::array<std::vector<Coord>::const_iterator, NUM_DIM> const &coordinate_iterators)
			: coordinate_iterators(coordinate_iterators)
	{}

	Position get_position() const
	{
		std::array<Coord, NUM_DIM> coordinates;
		for (auto const dimension : DIMENSIONS) {
			coordinates.at(dimension) = *coordinate_iterators.at(dimension);
		}
		return {coordinates};
	}

	auto const &get_coordinate_iterators() const
	{
		return coordinate_iterators;
	}

	bool operator==(Node const &rhs) const
	{
		return coordinate_iterators == rhs.coordinate_iterators;
	}

	Coord distance(Node const& other) const{
		return get_position().distance(other.get_position());
	}

	bool operator<(Node const &rhs) const
	{
		return coordinate_iterators < rhs.coordinate_iterators;
	}

private:
	std::array<std::vector<Coord>::const_iterator, NUM_DIM> coordinate_iterators;
};

}

#endif //CHIP_DESIGN_NODE_H
