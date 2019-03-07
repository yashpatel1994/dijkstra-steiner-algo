#ifndef CHIP_DESIGN_HEAP_H
#define CHIP_DESIGN_HEAP_H

#include <set>
#include <tuple>
#include <functional>
#include <assert.h>

namespace heap {

template<typename KeyType, typename DataType>
class Heap
{
private:
	struct DataEntry
	{
		bool operator<(DataEntry const &rhs) const;

		KeyType key;
		DataType data;
	};

public:
	Heap() :
			data()
	{}

	virtual void insert(KeyType const &key, DataType const &element);

	virtual void erase_if_exists(KeyType const &key, DataType const &element);

	virtual DataType pop_minimum();

private:
	std::set<DataEntry> data;
};

//// INLINE SECTION ////

template<typename KeyType, typename DataType>
bool Heap<KeyType, DataType>::DataEntry::operator<(heap::Heap<KeyType, DataType>::DataEntry const &rhs) const
{
	// This is faster than std::tie
	if (key < rhs.key) {
		return true;
	} else if (key > rhs.key) {
		return false;
	} else {
		return data < rhs.data;
	}
}

template<typename KeyType, typename DataType>
void Heap<KeyType, DataType>::insert(KeyType const &key, DataType const &element)
{
	data.insert({key, element});
}

template<typename KeyType, typename DataType>
void Heap<KeyType, DataType>::erase_if_exists(KeyType const &key, DataType const &element)
{
	data.erase({key, element});
}

template<typename KeyType, typename DataType>
DataType Heap<KeyType, DataType>::pop_minimum()
{
	assert(not data.empty());
	DataType const minimum_element = data.begin()->data;
	data.erase(data.begin());
	return minimum_element;
}


}

#endif //CHIP_DESIGN_HEAP_H
