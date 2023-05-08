#include "DetailWorker.h"

#include <cassert>

#include "DetailA.h"
#include "DetailB.h"
#include "DetailC.h"

template <typename T>
DetailWorker<T>::DetailWorker(std::string workerName, const int sleepTimeInSeconds, std::counting_semaphore<>* semaphore)
	:
	workerName(std::move(workerName)),
	sleepTimeInSeconds(sleepTimeInSeconds),
	semaphore(semaphore)
{
	assert(sleepTimeInSeconds > 0);
}

template <typename T>
void DetailWorker<T>::produceDetail()
{
	for (int i = 0; i < NUM_OF_DETAILS_TO_PRODUCE; ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(sleepTimeInSeconds));

		{
			std::lock_guard lockGuard(queueMutex);
			detailQueue.emplace(T());
		}

		printf("[%s] Detail produced. The queue length now is: %zu\n", workerName.c_str(), detailQueue.size());
		semaphore->release();
	}

	std::lock_guard lockGuard(activeMutex);
	active = false;
	printf("[%s] DetailWorker is inactive now.\n", workerName.c_str());
}

template <typename T>
std::optional<T> DetailWorker<T>::popDetail()
{
	std::lock_guard lockGuard(queueMutex);
	if (detailQueue.empty())
	{
		return {};
	}
	
	T returnDetail = detailQueue.front();
	detailQueue.pop();

	return returnDetail;
}

template <typename T>
bool DetailWorker<T>::isActive()
{
	std::lock_guard lockGuard(activeMutex);
	return active;
}

template <typename T>
bool DetailWorker<T>::isQueueEmpty()
{
	std::lock_guard lockGuard(queueMutex);
	return detailQueue.empty();
}

template class DetailWorker<DetailA>;
template class DetailWorker<DetailB>;
template class DetailWorker<DetailC>;