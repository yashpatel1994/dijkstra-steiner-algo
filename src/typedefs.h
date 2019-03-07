#ifndef CHIP_DESIGN_TYPEDEFS_H
#define CHIP_DESIGN_TYPEDEFS_H

#include <initializer_list>
#include <string>

using Coord = int;

static const int MAX_NUM_TERMINALS = 20;

enum Dimension
{
	DIM_X = 0,
	DIM_Y = 1,
	DIM_Z = 2,
	NUM_DIM = 3
};

auto const DIMENSIONS = {DIM_X, DIM_Y, DIM_Z};

inline std::string to_string(Dimension const dimension){
	switch (dimension) {
		case DIM_X:
			return "DIM_X";
		case DIM_Y:
			return "DIM_Y";
		case DIM_Z:
			return "DIM_Z";
		case NUM_DIM:
			return "NUM_DIM";
		default:
			abort();
	}
}

#endif //CHIP_DESIGN_TYPEDEFS_H
