#include "Reader.h"

std::vector<Terminal> Reader::read(std::istream &input) const
{
	std::vector<Terminal> terminals;
	size_t n;
	input >> n;
	for (size_t i = 0; i < n; i++) {
		input >> std::ws;
		if (input.eof()) {
			throw std::runtime_error("Malformed input: Input contains less than " + std::to_string(n) + " data rows.");
		}
		std::string line_buffer;
		std::getline(input, line_buffer);
		std::istringstream line_stream(line_buffer);

		Coord x, y, z;
		line_stream >> x >> y >> z >> std::ws;
		terminals.emplace_back(Position{x, y, z}, i);
		if (not line_stream.eof()) {
			throw std::runtime_error("Malformed input: Data line contains more than 3 numbers.");
		}
	}
	input >> std::ws;
	if (not input.eof()) {
		throw std::runtime_error("Malformed input: Input contains more than " + std::to_string(n) + " data rows.");
	}
	return terminals;
}
