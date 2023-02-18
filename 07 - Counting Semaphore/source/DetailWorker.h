#pragma once
#include <queue>
#include <mutex>
#include <semaphore>

#include "Detail.h"

class DetailWorker final
{
public:
	DetailWorker(const int workTimeInSeconds, std::counting_semaphore<>* semaphore);
	void produceDetail();
	void popDetail();
	[[nodiscard]] bool isActive() const;
	[[nodiscard]] bool isQueueEmpty();
private:
	constexpr static int NUM_OF_DETAILS_TO_PRODUCE = 10;

	bool active = true;
	const int workTimeInSeconds;

	std::counting_semaphore<>* semaphore;
	std::queue<Detail> detailQueue;
	std::mutex queueMutex;
};

