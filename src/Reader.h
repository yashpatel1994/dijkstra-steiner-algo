#ifndef CHIP_DESIGN_READER_H
#define CHIP_DESIGN_READER_H

#include <iosfwd>
#include <vector>
#include <sstream>
#include <iostream>
#include "Terminal.h"
#include "typedefs.h"

class Reader
{
public:
	std::vector<Terminal> read(std::istream &input) const;
};


#endif //CHIP_DESIGN_READER_H
