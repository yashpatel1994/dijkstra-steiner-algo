#ifndef CHIP_DESIGN_TERMINALS_H
#define CHIP_DESIGN_TERMINALS_H

#include "../../src/Terminal.h"
#include "../../src/TerminalSubset.h"
#include "../../src/graph/HananGridGraph.h"

struct ThreePositionsFixture{
	Position::Vector const positions = {
			{1, 1, 1},
			{2, 2, 2},
			{3, 3, 3}
	};

};

struct ThreeTerminalsFixture : public  ThreePositionsFixture{
	Terminal::Vector const terminals = {
			{positions.at(0), 0},
			{positions.at(1), 1},
			{positions.at(2), 2}
	};
	TerminalSubset const full = TerminalSubset::create_full(terminals);
	TerminalSubset const empty = TerminalSubset::create_empty(terminals);
	TerminalSubset const singleton_0 = TerminalSubset::create_singleton(terminals.at(0), terminals);
	TerminalSubset const singleton_1 = TerminalSubset::create_singleton(terminals.at(1), terminals);
	TerminalSubset const singleton_2 = TerminalSubset::create_singleton(terminals.at(2), terminals);
};

struct GraphFixture : public ThreeTerminalsFixture{
	graph::HananGridGraph G = {positions};
};

#endif //CHIP_DESIGN_TERMINALS_H
