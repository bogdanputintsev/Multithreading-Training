#pragma once
#include <array>
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
	constexpr static int NUMBER_OF_WORKERS = 3;
	
	std::array<std::shared_ptr<std::counting_semaphore<>>, NUMBER_OF_WORKERS> semaphores;
	std::shared_ptr<DetailWorker> workerA;
	std::shared_ptr<DetailWorker> workerB;
	std::shared_ptr<DetailWorker> workerC;
};

