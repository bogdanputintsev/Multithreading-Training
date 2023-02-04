#include "DetailWorker.h"

#include <cassert>

DetailWorker::DetailWorker(const int _workTimeInSeconds, std::counting_semaphore<10> *_semaphore)
	:
	workTimeInSeconds(_workTimeInSeconds),
	semaphore(_semaphore)
{
	assert(_workTimeInSeconds > 0);
}

void DetailWorker::produceDetail()
{
	for (int i = 0; i < NUM_OF_DETAILS_TO_PRODUCE; ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(workTimeInSeconds));

		std::lock_guard lockGuard(queueMutex);
		Detail detail;
		detailQueue.push(detail);
		printf("[DetailWorker %d] Detail produced. The queue length now is: %zu\n", workTimeInSeconds, detailQueue.size());
		//notifyCv->notify_all();
		semaphore->release();
	}

	active = false;
	printf("[DetailWorker %d] DetailWorker is inactive now.\n", workTimeInSeconds);
}

void DetailWorker::popDetail()
{
	std::lock_guard lockGuard(queueMutex);
	detailQueue.pop();
}

bool DetailWorker::isActive() const
{
	return active;
}

bool DetailWorker::isQueueEmpty()
{
	std::lock_guard lockGuard(queueMutex);
	return detailQueue.empty();
}
