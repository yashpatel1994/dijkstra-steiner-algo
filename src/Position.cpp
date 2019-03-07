#include "Position.h"

bool Position::operator==(Position const &rhs) const
{
	bool const equality = coordinates == rhs.coordinates;
	return equality;
}
