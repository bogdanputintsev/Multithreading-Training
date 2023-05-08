#pragma once
#include <array>
#include <chrono>
#include <semaphore>

#include "DetailWorker.h"
#include "DetailA.h"
#include "DetailC.h"
#include "DetailB.h"

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
	std::shared_ptr<DetailWorker<DetailA>> workerA;
	std::shared_ptr<DetailWorker<DetailB>> workerB;
	std::shared_ptr<DetailWorker<DetailC>> workerC;
};

