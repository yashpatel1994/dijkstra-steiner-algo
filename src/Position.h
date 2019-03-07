#ifndef CHIP_DESIGN_POSITION3D_H
#define CHIP_DESIGN_POSITION3D_H

#include <string>
#include <array>
#include <vector>
#include "typedefs.h"

class Position
{
public:
	using Vector = std::vector<Position>;

	Coord coord(Dimension const dimension) const
	{
		return coordinates.at(dimension);
	}

	std::string to_string() const
	{
		std::string string_representation = "[";

		for (auto const dimension : DIMENSIONS) {
			string_representation += ::to_string(dimension) + "=" + std::to_string(coord(dimension)) + ", ";
		}

		//remove trailing delimiter
		string_representation.pop_back();
		string_representation.pop_back();

		string_representation += "]";
		return string_representation;
	}

	Coord distance(Position const &other) const
	{
		Coord distance = 0;
		for (auto const &dimension : DIMENSIONS) {
			distance += std::abs(coord(dimension) - other.coord(dimension));
		}
		return distance;
	}

	bool operator==(Position const &rhs) const;

public:
	std::array<Coord, NUM_DIM> coordinates;
};


#endif //CHIP_DESIGN_POSITION3D_H
