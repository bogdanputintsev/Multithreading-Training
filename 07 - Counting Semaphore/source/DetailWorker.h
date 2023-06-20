#pragma once
#include <mutex>
#include <semaphore>

class DetailWorker final
{
public:
	DetailWorker(std::string workerName, int sleepTimeInSeconds, std::shared_ptr<std::counting_semaphore<>> semaphore);
	void produceDetail();
	void popDetail();
	[[nodiscard]] bool isActive();
private:
	constexpr static int NUMBER_OF_DETAILS_TO_PRODUCE = 10;

	bool active = true;
	const std::string workerName;
	const int sleepTimeInSeconds;

	std::shared_ptr<std::counting_semaphore<>> semaphore;
	std::mutex activeMutex;

	int numberOfFreeDetails;
	std::mutex numberOfFreeDetailsMutex;
};

