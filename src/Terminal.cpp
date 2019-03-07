

#include "Terminal.h"

Terminal::Terminal(Position const &position, Terminal::Index const index) : position(position), index(index)
{}

bool Terminal::operator==(Terminal const &rhs) const
{
	return position == rhs.position;
}

bool Terminal::operator!=(Terminal const &rhs) const
{
	return !(rhs == *this);
}

Position const &Terminal::get_position() const
{
	return position;
}

Terminal::Index Terminal::get_index() const
{
	return index;
}
