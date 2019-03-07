#include <algorithm>
#include "HananGridGraph.h"

namespace graph {

void HananGridGraph::add_feasible_position(Position const &position)
{
	for (auto const dimension : DIMENSIONS) {
		auto& dimension_coordinates = coordinates(dimension);
		auto const& new_value = position.coord(dimension);
		auto const insertion_position
				= std::lower_bound(dimension_coordinates.begin(), dimension_coordinates.end(), new_value);
		if(insertion_position == dimension_coordinates.end() or *insertion_position != new_value){
			dimension_coordinates.insert(insertion_position, position.coord(dimension));
		}
	}
}

std::vector<Node> HananGridGraph::neighbors(Node const &node) const
{
	std::vector<Node> neighbors;
	auto const &coordinate_iterators = node.get_coordinate_iterators();
	for (auto const dimension : DIMENSIONS) {
		if (coordinate_iterators.at(dimension) != dimension_coordinates.at(dimension).begin()) {
			auto coordinate_iterators_copy = coordinate_iterators;
			coordinate_iterators_copy.at(dimension)--;
			neighbors.emplace_back(coordinate_iterators_copy);
		}
		if (coordinate_iterators.at(dimension) != std::prev(dimension_coordinates.at(dimension).end())) {
			auto coordinate_iterators_copy = coordinate_iterators;
			coordinate_iterators_copy.at(dimension)++;
			neighbors.emplace_back(coordinate_iterators_copy);
		}
	}
	return neighbors;
}

Node HananGridGraph::create_node(Position const &position) const
{
	std::array<HananGridGraph::Coordinates::const_iterator, NUM_DIM> coordinate_iterators;
	for (auto const dimension : DIMENSIONS) {
		coordinate_iterators.at(dimension)
				= std::lower_bound(coordinates(dimension).begin(), coordinates(dimension).end(), position.coord(dimension));
		assert(coordinate_iterators.at(dimension) != coordinates(dimension).end());
	}
	return  {coordinate_iterators};
}

HananGridGraph::Coordinates &HananGridGraph::coordinates(Dimension const dimension)
{
	return dimension_coordinates.at(dimension);
}

HananGridGraph::Coordinates const &HananGridGraph::coordinates(Dimension const dimension) const
{
	return dimension_coordinates.at(dimension);
}

size_t HananGridGraph::get_index(Node const &node) const
{
	size_t sum = 0;
	size_t offset = 1;
	for (auto const &dimension : DIMENSIONS) {
		sum += offset *
			   std::distance(coordinates(dimension).begin(), node.get_coordinate_iterators().at(dimension));
		offset *= coordinates(dimension).size();
	}
	assert(sum < num_nodes());
	return sum;
}

size_t HananGridGraph::num_nodes() const
{
	size_t num = 1;
	for (auto const &dimension : DIMENSIONS) {
		num *= coordinates(dimension).size();
	}
	return num;
}


}