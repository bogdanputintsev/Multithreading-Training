#pragma once

#include<thread>
#include<mutex>

class PhilosphersTable
{
public:
	void startDinner();

protected:
	void philosopherJob(std::mutex& leftFork, std::mutex& rightFork, const int philosopherNum);
	int takeFood();
	void takeFork(std::mutex& fork, const int philosopherNum, const std::string& hand);
	void releaseFork(std::mutex& fork);

private:
	static const int NUM_PHILOSOPHERS = 5;
	static const int NUM_FOOD = 50;

	int foodLeft = NUM_FOOD;

	std::mutex food;
	std::mutex forks[NUM_PHILOSOPHERS];
	std::thread philosophers[NUM_PHILOSOPHERS];
};

