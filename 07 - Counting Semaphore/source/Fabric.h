#pragma once
#include <vector>
#include <chrono>

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

	std::mutex consumerMutex;
	std::condition_variable consumerCv;
	std::vector<std::shared_ptr<DetailWorker>> detailWorkers;
};

