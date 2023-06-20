#include "DetailWorker.h"

#include <cassert>

DetailWorker::DetailWorker(std::string workerName, const int sleepTimeInSeconds,
                           std::shared_ptr<std::counting_semaphore<>> semaphore)
	:
	workerName(std::move(workerName)),
	sleepTimeInSeconds(sleepTimeInSeconds),
	semaphore(std::move(semaphore)),
	numberOfFreeDetails(0)
{
	assert(sleepTimeInSeconds > 0);
}

void DetailWorker::produceDetail()
{
	for (int i = 0; i < NUMBER_OF_DETAILS_TO_PRODUCE; ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(sleepTimeInSeconds));

		{
			std::lock_guard lock{ numberOfFreeDetailsMutex };
			++numberOfFreeDetails;
			printf("[%s] Detail produced. The queue length now is: %d\n", workerName.c_str(), numberOfFreeDetails);
		}
		semaphore->release();
	}

	std::lock_guard lockGuard{ activeMutex };
	active = false;
	printf("[%s] DetailWorker is inactive now.\n", workerName.c_str());
}

void DetailWorker::popDetail()
{
	std::lock_guard lock{ numberOfFreeDetailsMutex };
	--numberOfFreeDetails;
}

bool DetailWorker::isActive()
{
	std::lock_guard lockGuard(activeMutex);
	return active;
}