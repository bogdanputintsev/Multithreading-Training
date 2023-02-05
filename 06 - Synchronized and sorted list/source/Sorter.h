#pragma once

#include <semaphore>

#include "SynchronizedList.h"

class Sorter final : public Observer
{
public:
	explicit Sorter(SynchronizedList* synchronizedList);
	Sorter() = delete;
	Sorter(const Sorter&) = delete;
	Sorter(Sorter&&) = delete;
	~Sorter() override = default;
	Sorter& operator=(const Sorter&) = delete;
	Sorter& operator=(Sorter&&) = delete;

	virtual void update() override;

	void sortLoop();
	bool sort(const SortAlgorithm& sortAlgorithm);
	void stop();
private:
	bool isRunning = true;
	SynchronizedList* synchronizedList = nullptr;

	std::binary_semaphore sortSemaphore{ 0 };

	static constexpr int SORT_WAIT_FOR_SECS = 5;
};

