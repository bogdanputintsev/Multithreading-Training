#pragma once
#include <queue>
#include <mutex>
#include "Detail.h"

class DetailWorker final
{
public:
	DetailWorker(const int _workTimeInSeconds, std::condition_variable* _cv);
	void produceDetail();
	void popDetail();
	[[nodiscard]] bool isActive() const;
	[[nodiscard]] bool isQueueEmpty();
private:
	bool active = true;
	const int workTimeInSeconds;
	std::condition_variable* notifyCv;
	std::queue<Detail> detailQueue;
	std::mutex queueMutex;
	
	const int NUM_OF_DETAILS_TO_PRODUCE = 10;
};

