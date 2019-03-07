#include <iostream>
#include <fstream>
#include "Reader.h"
#include "dijkstra_steiner_algorithm/DijkstraSteinerAlgorithm.h"

void print_usage(const char *argv[])
{
	std::cout
			<< "Calculates the length of a minimum Steiner Tree for the given instance file."
			<< "Usage: " << argv[0] << " file" << std::endl;
}

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		print_usage(argv);
		return 1;
	}

	try {
		Reader reader;
		std::ifstream input_file(argv[1]);
		if (input_file.bad() or input_file.fail()) {
			throw std::runtime_error("Cannot open file: " + std::string(argv[1]));
		}
		auto const terminals = reader.read(input_file);

		if(terminals.size() > MAX_NUM_TERMINALS){
			throw std::runtime_error("Cannot handle instances with more than 20 terminals.");
		}

		dijkstra_steiner_algorithm::Instance const instance = dijkstra_steiner_algorithm::Instance::create(terminals);
		dijkstra_steiner_algorithm::DijkstraSteinerAlgorithm algorithm(instance);
		std::cout << algorithm.calculate_minimum_steiner_tree_length() << std::endl;
	} catch (std::exception const &e) {
		std::cout << "Exception occurred: " << e.what() << std::endl;
		return 1;
	}

	return EXIT_SUCCESS;
}

