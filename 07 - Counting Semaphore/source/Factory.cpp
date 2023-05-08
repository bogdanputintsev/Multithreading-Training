#include "Factory.h"

#include <cassert>

#include "Module.h"
#include "Widget.h"

void DetailWorker<DetailA>::produceDetail();

void Factory::run()
{
	std::vector<std::thread> detailWorkerThreads;
	std::thread detailConsumerThread(&Factory::detailConsumer, this);
	
	for (int i = 0; i < NUM_OF_WORKERS; i++)
	{
		semaphores[i] = std::make_shared<std::counting_semaphore<>>(0);
	}
	
	assert(semaphores.size() == NUM_OF_WORKERS);

	workerA = std::make_shared<DetailWorker<DetailA>>("Worker A", 1, semaphores[0].get());
	detailWorkerThreads.emplace_back(&DetailWorker<DetailA>::produceDetail, workerA.get());
	
	workerB = std::make_shared<DetailWorker<DetailB>>("Worker B", 2, semaphores[1].get());
	detailWorkerThreads.emplace_back(&DetailWorker<DetailB>::produceDetail, workerB.get());

	workerC = std::make_shared<DetailWorker<DetailC>>("Worker C", 3, semaphores[2].get());
	detailWorkerThreads.emplace_back(&DetailWorker<DetailC>::produceDetail, workerC.get());

	
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

		auto detailA = workerA->popDetail();
		auto detailB = workerB->popDetail();
		auto detailC = workerC->popDetail();
		if (!detailA.has_value() || !detailB.has_value() || !detailC.has_value())
		{
			throw std::runtime_error("Semaphore was acquired, but detail is missing.");
		}

		Module module(detailA.value(), detailB.value());
		printf("[DetailConsumer] Module from details A and B has been created.\n");

		[[maybe_unused]] Widget widget(module, detailC.value());
		printf("[DetailConsumer] Widget is ready.\n");

		printf("[DetailConsumer] Detail consumed.\n");
	}
}

bool Factory::programHasToRun() const
{
	return workerA->isActive() && workerB->isActive() && workerC->isActive();
}
