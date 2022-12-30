#pragma once

#include <iostream>
#include <cassert>
#include <list>
#include "Data.h"

class SortAlgorithm
{
public:
	virtual ~SortAlgorithm() = default;
	virtual void sort(Data* front, Data * end) = 0;
};

