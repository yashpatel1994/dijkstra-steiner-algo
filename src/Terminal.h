#ifndef CHIP_DESIGN_TERMINAL_H
#define CHIP_DESIGN_TERMINAL_H

#include <vector>
#include "Position.h"

class Terminal
{
public:
	using Vector = std::vector<Terminal>;
	using Index = size_t;

	Terminal(Position const &position, Terminal::Index const index);

	bool operator==(Terminal const &rhs) const;

	bool operator!=(Terminal const &rhs) const;

	Position const &get_position() const;

	Index get_index() const;

private:
	Position const position;
	Index const index;
};


#endif //CHIP_DESIGN_TERMINAL_H
