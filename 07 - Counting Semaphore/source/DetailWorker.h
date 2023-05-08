#pragma once
#include <queue>
#include <mutex>
#include <optional>
#include <semaphore>

template <typename T>
class DetailWorker final
{
public:
	DetailWorker(std::string workerName, int sleepTimeInSeconds, std::counting_semaphore<>* semaphore);
	void produceDetail();
	std::optional<T> popDetail();
	[[nodiscard]] bool isActive();
	[[nodiscard]] bool isQueueEmpty();
private:
	constexpr static int NUM_OF_DETAILS_TO_PRODUCE = 10;

	bool active = true;
	const std::string workerName;
	const int sleepTimeInSeconds;

	std::counting_semaphore<>* semaphore;
	std::queue<T> detailQueue;
	std::mutex queueMutex;
	std::mutex activeMutex;
};

