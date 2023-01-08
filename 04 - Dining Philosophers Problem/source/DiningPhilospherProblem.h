#pragma once

#include<thread>
#include<mutex>
#include<array>

class PhilosophersTable final
{
public:
	void startDinner();

private:
	void philosopherJob(std::mutex& leftFork, std::mutex& rightFork, const int philosopherNum);
	int takeFood();
	static void takeFork(std::mutex& fork, const int philosopherNum, const std::string& hand);
	static void releaseFork(std::mutex& fork);
	
	int foodLeft = NUM_FOOD;

	static constexpr int NUM_PHILOSOPHERS = 5;
	static constexpr int NUM_FOOD = 50;
	static constexpr int NUM_FORKS = NUM_PHILOSOPHERS;
	static constexpr int NUM_MS_TO_WAIT = 1500;

	std::mutex food;
	std::array<std::mutex, NUM_FORKS> forks;
	std::array<std::thread, NUM_PHILOSOPHERS> philosophers;
};

