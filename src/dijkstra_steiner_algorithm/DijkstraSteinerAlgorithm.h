#ifndef CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H
#define CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H


#include "../graph/HananGridGraph.h"
#include "../Terminal.h"
#include "../heap/Heap.h"
#include "../utils.h"
#include "../TerminalSubset.h"
#include "Labels.h"
#include "lower_bound/BoundingBoxLowerBound.h"
#include "lower_bound/OneTreeLowerBound.h"
#include "Instance.h"

namespace dijkstra_steiner_algorithm {

class DijkstraSteinerAlgorithm
{
public:
	DijkstraSteinerAlgorithm(Instance const &instance) :
			instance(instance),
			labels(instance),
			heap(),
			lower_bound_oracle_bb(instance.terminals),
			lower_bound_oracle_one_tree(instance.terminals)
	{}

	Coord calculate_minimum_steiner_tree_length()
	{
		auto const T_minus_t = TerminalSubset::create_full(instance.terminals)
				.minus(TerminalSubset::create_singleton(instance.t, instance.terminals));

		// Line 1
		generate_initial_labels();

		// Line 3
		while (true) {
			auto const v_I = heap.pop_minimum();
			auto const &v = v_I.node;
			auto const &I = v_I.subset;
			auto const label_of_v_I = labels.get(v_I);

			if (labels.is_permanently_labeled(v_I)) {
				continue;
			}

			// Line 4
			labels.mark_permanently_labeled(v_I);

			// Line 5
			if (v.get_position() == instance.t.get_position() and I == T_minus_t) {
				return labels.get(v_I);
			}

			// Line 6
			update_neighbors(v, I, label_of_v_I);

			// Line 7
			update_with_permanently_labeled(v, I, label_of_v_I);

		}
	}

private:
	void generate_initial_labels();

	void update_with_permanently_labeled(
			graph::Node const &v,
			TerminalSubset const &I,
			Coord const label_of_v_I
	);

	void update_neighbors(
			graph::Node const &v,
			TerminalSubset const &I,
			Coord const label_of_v_I
	);

	void update_label(
			heap::Heap<Coord, NodePlusTerminalSubset> &heap,
			NodePlusTerminalSubset const &v_I,
			Coord const new_l_value
	);

	Coord lower_bound(
			NodePlusTerminalSubset node_plus_terminal_subset
	);


	Instance const &instance;
	Labels labels;
	heap::Heap<Coord, NodePlusTerminalSubset> heap;
	lower_bound::BoundingBoxLowerBound lower_bound_oracle_bb;
	lower_bound::OneTreeLowerBound lower_bound_oracle_one_tree;
};



//// INLINE SECTION ////

inline void dijkstra_steiner_algorithm::DijkstraSteinerAlgorithm::generate_initial_labels()
{
	for (auto const &terminal : instance.terminals) {
		NodePlusTerminalSubset const node_plus_subset
				= {
						instance.graph.create_node(terminal.get_position()),
						TerminalSubset::create_singleton(terminal, instance.terminals)
				};
		update_label(heap, node_plus_subset, 0);
	}
}

inline void DijkstraSteinerAlgorithm::update_with_permanently_labeled(graph::Node const &v, TerminalSubset const &I,
		Coord const label_of_v_I
)
{
	auto const T_minus_I_and_t =
			TerminalSubset::create_full(instance.terminals)
					.minus(I)
					.minus(TerminalSubset::create_singleton(instance.t, instance.terminals));
	for (auto const &J : labels.get_permanently_labeled_subsets_for_node(v)) {
		if (T_minus_I_and_t.contains(J)) {
			auto const I_union_J = TerminalSubset{I}.plus(J);
			NodePlusTerminalSubset const v_I_union_J = {v, I_union_J};
			Coord new_l_value =
					std::min(
							labels.get(v_I_union_J),
							label_of_v_I + labels.get(NodePlusTerminalSubset{v, J})
					);
			update_label(heap, v_I_union_J, new_l_value);
		}
	}
}

inline void DijkstraSteinerAlgorithm::update_neighbors(
		graph::Node const &v,
		TerminalSubset const &I,
		Coord const label_of_v_I
)
{
	for (auto const &neighbor : instance.graph.neighbors(v)) {
		Coord new_l_value = label_of_v_I + v.distance(neighbor);
		NodePlusTerminalSubset const w_I = {neighbor, I};
		if (new_l_value < labels.get(w_I)) {
			update_label(heap, w_I, new_l_value);
		}
	}
}

inline void DijkstraSteinerAlgorithm::update_label(heap::Heap<Coord, NodePlusTerminalSubset> &heap,
		NodePlusTerminalSubset const &v_I,
		Coord const new_l_value
)
{
	Coord const old_value = labels.get(v_I);
	Coord const lb = lower_bound({v_I.node, v_I.subset.complement()});
	heap.erase_if_exists(old_value + lb, v_I);
	heap.insert(new_l_value + lb, v_I);
	labels.set(v_I, new_l_value);
}

inline Coord DijkstraSteinerAlgorithm::lower_bound(NodePlusTerminalSubset node_plus_terminal_subset)
{
	return std::max(
			lower_bound_oracle_one_tree.lower_bound(
					node_plus_terminal_subset.node,
					node_plus_terminal_subset.subset
			),
			lower_bound_oracle_bb.lower_bound(
					node_plus_terminal_subset.node,
					node_plus_terminal_subset.subset
			)
	);
}


}

#endif //CHIP_DESIGN_DIJKSTRASTEINERALGORITHM_H
