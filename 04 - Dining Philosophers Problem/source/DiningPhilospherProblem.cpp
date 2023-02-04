#include "DiningPhilospherProblem.h"

/*
 * Method initializes the philosophers threads and starts the dinner.
 */
void PhilosophersTable::startDinner()
{
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		philosophers[i] = std::thread(&PhilosophersTable::philosopherJob, this, std::ref(forks[i]), std::ref(forks[(i + 1) % NUM_PHILOSOPHERS]), i);
	}

	for (auto& philosopher : philosophers)
	{
		philosopher.join();
	}
}

/*
 * Method simulates the philosopher's job.
 * @param leftFork - the left fork of the philosopher.
 * @param rightFork - the right fork of the philosopher.
 * @param philosopherNum - the number of the philosopher.
 */
void PhilosophersTable::philosopherJob(std::mutex& leftFork, std::mutex& rightFork, const int philosopherNum)
{
	printf("[Philosopher %d]: sitting down to dinner.\n", philosopherNum + 1);

	int foodNumber = takeFood();
	while (foodNumber > 0)
	{
		printf("[Philosopher %d]: get dish %d.\n", philosopherNum + 1, foodNumber);
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
		std::this_thread::sleep_for(std::chrono::milliseconds(NUM_MS_TO_WAIT));
		releaseFork(leftFork);
		releaseFork(rightFork);

		foodNumber = takeFood();
	}

	printf("[Philosopher %d]: is done eating.\n", philosopherNum + 1);
}

/*
 * Decrements the food left and returns the new value.
 */
int PhilosophersTable::takeFood()
{
	std::lock_guard<std::mutex> foodLock(food);
	foodLeft--;
	return foodLeft;
}

/*
 * Locks the fork.
 */
void PhilosophersTable::takeFork(std::mutex& fork, const int philosopherNum, const std::string& hand)
{
	fork.lock();
	printf("[Philosopher %d]: got %s fork\n", philosopherNum + 1, hand.c_str());
}

/*
 * Unlocks the fork.
 */
void PhilosophersTable::releaseFork(std::mutex& fork)
{
	fork.unlock();
}
