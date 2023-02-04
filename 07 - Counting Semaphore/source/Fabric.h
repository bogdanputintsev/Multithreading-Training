#pragma once
#include <array>
#include <vector>
#include <chrono>
#include <semaphore>

#include "DetailWorker.h"

class Fabric final
{
public:
	Fabric() = default;
	void run();
	[[nodiscard]] bool programHasToRun() const;
private:
	void detailConsumer();

	constexpr static int NUM_OF_WORKERS = 3;
	constexpr static int MAX_NUM_OF_DETAILS_TO_PRODUCE = 10;
	std::array<std::counting_semaphore<MAX_NUM_OF_DETAILS_TO_PRODUCE>, NUM_OF_WORKERS> semaphores;
	
	std::mutex consumerMutex;
	std::condition_variable consumerCv;
	std::vector<std::shared_ptr<DetailWorker>> detailWorkers;
};

