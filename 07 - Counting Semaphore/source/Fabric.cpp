#include "Fabric.h"

void Fabric::run()
{
	std::vector<std::thread> detailWorkerThreads;
	std::thread detailConsumerThread(&Fabric::detailConsumer, this);
	
	for (int i = 0; i < NUM_OF_WORKERS; ++i)
	{
		//detailWorkers.emplace_back(std::make_shared<DetailWorker>(i + 1, &semaphores[i]));
		detailWorkerThreads.emplace_back(&DetailWorker::produceDetail, detailWorkers.back());
	}
	
	for (auto& detailWorkerThread : detailWorkerThreads)
	{
		detailWorkerThread.join();
	}
	
	detailConsumerThread.join();
}

void Fabric::detailConsumer()
{
	while (programHasToRun())
	{
		printf("[DetailConsumer] Waiting for details...\n");
		for (auto& semaphore : semaphores)
		{
			semaphore.acquire();
		}

		for (const auto& detailWorker : detailWorkers)
		{
			detailWorker->popDetail();
		}

		printf("[DetailConsumer] Detail consumed.\n");
	}
}

bool Fabric::programHasToRun() const
{
	return std::ranges::all_of(detailWorkers, [](const auto& detailWorker)
		{
			return detailWorker->isActive();
		});
}
