#include <thread>
#include <mutex>
#include <vector>
#include <cassert>
#include <iostream>

namespace
{
	const int NUM_PHILOSOPHERS = 5;
	const int NUM_FOOD = 50;

	static std::atomic<int> foodLeft = NUM_FOOD;

	std::mutex forkLock[NUM_PHILOSOPHERS];

	struct Fork
	{
		std::mutex mutex;
	};

	int foodOnTable();
	void takeFork(Fork& fork, const int philosopherNum, const std::string& hand);
	void releaseForks(Fork& leftFork, Fork& rightFork);

	void philosopherJob(Fork& leftFork, Fork& rightFork, const int philosopherNum)
	{
		printf("[Philosopher %d]: sitting down to dinner.\n", philosopherNum + 1);

		int food = 0;
		while ((food = foodOnTable()))
		{
			printf("[Philosopher %d]: get dish %d.\n", philosopherNum + 1, food);
			if ((philosopherNum & 1) == 0)
			{
				takeFork(rightFork, philosopherNum, "right");
				takeFork(leftFork, philosopherNum, "left");
			}
			else
			{
				takeFork(leftFork, philosopherNum, "left");
				takeFork(rightFork, philosopherNum, "right");
			}

			printf("[Philosopher %d]: is eating...\n", philosopherNum + 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			releaseForks(leftFork, rightFork);
		}

		printf("[Philosopher %d]: is done eating.\n", philosopherNum + 1);
	}

	int foodOnTable()
	{
		foodLeft = std::max(foodLeft - 1, 0);
		return foodLeft;
	}

	void takeFork(Fork& fork, const int philosopherNum, const std::string& hand)
	{
		fork.mutex.lock();
		printf("[Philosopher %d]: got %s fork\n", philosopherNum + 1, hand.c_str());
	}

	void releaseForks(Fork& leftFork, Fork& rightFork)
	{
		leftFork.mutex.unlock();
		rightFork.mutex.unlock();
	}
}

int main()
{
	assert(NUM_PHILOSOPHERS > 1);

	Fork forks[NUM_PHILOSOPHERS];
	std::thread philosophers[NUM_PHILOSOPHERS];
	
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		philosophers[i] = std::thread(philosopherJob, std::ref(forks[i]), std::ref(forks[(i + 1) % NUM_PHILOSOPHERS]), i);
	}

	for (auto& philosopher : philosophers)
	{
		philosopher.join();
	}

	return EXIT_SUCCESS;
}
