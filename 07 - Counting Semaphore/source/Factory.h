#pragma once
#include <array>
#include <vector>
#include <chrono>
#include <semaphore>

#include "DetailWorker.h"

class Factory final
{
public:
	Factory() = default;
	void run();
	[[nodiscard]] bool programHasToRun() const;
private:
	void detailConsumer() const;
	constexpr static int NUM_OF_WORKERS = 3;
	
	std::array<std::shared_ptr<std::counting_semaphore<>>, NUM_OF_WORKERS> semaphores;
	std::vector<std::shared_ptr<DetailWorker>> detailWorkers;
};

