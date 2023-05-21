#pragma once

#include "Data.h"

class SortAlgorithm
{
public:
	SortAlgorithm() = default;
	SortAlgorithm& operator=(const SortAlgorithm&) = delete;
	SortAlgorithm& operator=(SortAlgorithm&&) = delete;
	SortAlgorithm(const SortAlgorithm&) = delete;
	SortAlgorithm(SortAlgorithm&&) = delete;
	virtual ~SortAlgorithm() = default;

	virtual void sort(Data* front) const = 0;

};

