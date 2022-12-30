#pragma once

#include "SortAlgorithm.h"

class BubbleSort : public SortAlgorithm
{
public:
	BubbleSort() = default;
	virtual ~BubbleSort() override = default;
	virtual void sort(Data* front, Data* end) override;
};

