#ifndef COMBINATORIAL_OPTIMIZATION_UTILS_H
#define COMBINATORIAL_OPTIMIZATION_UTILS_H

#include <numeric>
#include <algorithm>
#include <functional>

/**
 * Creates {0,1,...,n-1}
 */
template<typename Scalar>
std::vector<Scalar> create_0_to_n_minus_one(Scalar const n)
{
	std::vector<Scalar> elements(n);
	std::iota(elements.begin(), elements.end(), 0);
	return elements;
}

template<typename ResultType, typename Container, typename Filter>
std::vector<ResultType> transform(Container const &container, Filter const &filter)
{
	std::vector<ResultType> result;
	std::transform(container.begin(), container.end(), std::inserter(result, result.begin()), filter);
	return result;
}

/**
 * Given a vector and a binary predicate f, return a vector
 * containing only those elements for which f returns true.
 * @param vector
 * @param filter Binary predicate
 * @return
 */
template<typename T>
std::vector<T> filter(std::vector<T> const &vector, std::function<bool(T const &)> const &filter)
{
	std::vector<T> filtered_vector;
	for (auto const &element : vector) {
		if (filter(element)) {
			filtered_vector.push_back(element);
		}
	}
	return filtered_vector;
}

template<typename ContainerA, typename ContainerB = ContainerA>
void append(ContainerA &target, ContainerB const &new_values)
{
	target.insert(target.end(), new_values.begin(), new_values.end());
}

//TODO improve, if this becomes bottleneck
inline size_t pow2(size_t const exponent){
	size_t result = 1;
	for(size_t i = 0; i < exponent; i++){
		result *= 2;
	}
	return result;
}

#endif //COMBINATORIAL_OPTIMIZATION_UTILS_H
