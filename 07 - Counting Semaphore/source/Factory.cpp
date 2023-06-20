#include "Factory.h"

#include <cassert>

void Factory::run()
{
	std::vector<std::thread> detailWorkerThreads;
	std::thread detailConsumerThread { &Factory::detailConsumer, this };
	
	for (int i = 0; i < NUMBER_OF_WORKERS; i++)
	{
		semaphores[i] = std::make_shared<std::counting_semaphore<>>(0);
	}
	
	assert(semaphores.size() == NUMBER_OF_WORKERS);

	workerA = std::make_shared<DetailWorker>("Worker A", 1, semaphores[0]);
	detailWorkerThreads.emplace_back(&DetailWorker::produceDetail, workerA);
	
	workerB = std::make_shared<DetailWorker>("Worker B", 2, semaphores[1]);
	detailWorkerThreads.emplace_back(&DetailWorker::produceDetail, workerB);

	workerC = std::make_shared<DetailWorker>("Worker C", 3, semaphores[2]);
	detailWorkerThreads.emplace_back(&DetailWorker::produceDetail, workerC);

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
		semaphores[0]->acquire();
		semaphores[1]->acquire();

		workerA->popDetail();
		workerB->popDetail();
		printf("[DetailConsumer] Module from details A and B has been created.\n");

		semaphores[2]->acquire();
		workerC->popDetail();

		printf("[DetailConsumer] Widget is ready.\n");
		printf("[DetailConsumer] Detail consumed.\n");
	}
}

bool Factory::programHasToRun() const
{
	return workerA->isActive() && workerB->isActive() && workerC->isActive();
}
