#pragma once

#include "SortAlgorithm.h"

class BubbleSort final : public SortAlgorithm
{
public:
	BubbleSort() = default;
	BubbleSort(const BubbleSort&) = delete;
	BubbleSort(BubbleSort&&) = delete;
	BubbleSort& operator=(const BubbleSort&) = delete;
	BubbleSort& operator=(BubbleSort&&) = delete;

	virtual ~BubbleSort() override = default;
	virtual void sort(Data* front, Data* end) const override;
};

