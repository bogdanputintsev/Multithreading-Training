#include "Factory.h"

void Factory::run()
{
	std::vector<std::thread> detailWorkerThreads;
	std::thread detailConsumerThread(&Factory::detailConsumer, this);
	
	for (int i = 0; i < NUM_OF_WORKERS; i++)
	{
		semaphores[i] = std::make_shared<std::counting_semaphore<>>(0);
		detailWorkers.emplace_back(std::make_shared<DetailWorker>(i + 1, semaphores[i].get()));
		detailWorkerThreads.emplace_back(&DetailWorker::produceDetail, detailWorkers.back());
	}
	
	for (auto& detailWorkerThread : detailWorkerThreads)
	{
		detailWorkerThread.join();
	}
	
	detailConsumerThread.join();
}

void Factory::detailConsumer() const
{
	while (programHasToRun())
	{
		printf("[DetailConsumer] Waiting for details...\n");
		for (auto& semaphore : semaphores)
		{
			semaphore->acquire();
		}

		for (const auto& detailWorker : detailWorkers)
		{
			detailWorker->popDetail();
		}

		printf("[DetailConsumer] Detail consumed.\n");
	}
}

bool Factory::programHasToRun() const
{
	return std::ranges::all_of(detailWorkers, [](const auto& detailWorker)
		{
			return detailWorker->isActive();
		});
}
