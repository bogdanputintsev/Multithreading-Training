#pragma once
#include <queue>
#include <mutex>
#include <semaphore>

#include "Detail.h"

class DetailWorker final
{
public:
	DetailWorker(const int _workTimeInSeconds, std::counting_semaphore<10>* _semaphore);
	void produceDetail();
	void popDetail();
	[[nodiscard]] bool isActive() const;
	[[nodiscard]] bool isQueueEmpty();
private:
	const int NUM_OF_DETAILS_TO_PRODUCE = 10;

	bool active = true;
	const int workTimeInSeconds;

	std::counting_semaphore<10>* semaphore;
	//std::condition_variable* notifyCv;
	std::queue<Detail> detailQueue;
	std::mutex queueMutex;
	
};

